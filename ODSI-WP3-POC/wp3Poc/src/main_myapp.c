/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/

/******************************************************************************
 * NOTE 1: The Win32 port is a simulation (or is that emulation?) only!  Do not
 * expect to get real time behaviour from the Win32 port or this demo
 * application.  It is provided as a convenient development and demonstration
 * test bed only.  This was tested using Windows XP on a dual core laptop.
 *
 * Windows will not be running the FreeRTOS simulator threads continuously, so
 * the timing information in the FreeRTOS+Trace logs have no meaningful units.
 * See the documentation page for the Windows simulator for an explanation of
 * the slow timing:
 * http://www.freertos.org/FreeRTOS-Windows-Simulator-Emulator-for-Visual-Studio-and-Eclipse-MingW.html
 * - READ THE WEB DOCUMENTATION FOR THIS PORT FOR MORE INFORMATION ON USING IT -
 *
 * NOTE 2:  This project provides two demo applications.  A simple blinky style
 * project, and a more comprehensive test and demo application.  The
 * mainCREATE_SIMPLE_BLINKY_DEMO_ONLY setting in main.c is used to select
 * between the two.  See the notes on using mainCREATE_SIMPLE_BLINKY_DEMO_ONLY
 * in main.c.  This file implements the simply blinky style version.
 *
 * NOTE 3:  This file only contains the source code that is specific to the
 * basic demo.  Generic functions, such FreeRTOS hook functions, are defined
 * in main.c.
 ******************************************************************************
 *
 * main_blinky() creates one queue, and two tasks.  It then starts the
 * scheduler.
 *
 * The Queue Send Task:
 * The queue send task is implemented by the prvQueueSendTask() function in
 * this file.  prvQueueSendTask() sits in a loop that causes it to repeatedly
 * block for 200 (simulated as far as the scheduler is concerned, but in
 * reality much longer - see notes above) milliseconds, before sending the
 * value 100 to the queue that was created within main_blinky().  Once the
 * value is sent, the task loops back around to block for another 200
 * (simulated) milliseconds.
 *
 * The Queue Receive Task:
 * The queue receive task is implemented by the prvQueueReceiveTask() function
 * in this file.  prvQueueReceiveTask() sits in a loop where it repeatedly
 * blocks on attempts to read data from the queue that was created within
 * main_blinky().  When data is received, the task checks the value of the
 * data, and if the value equals the expected 100, outputs a message.  The
 * 'block time' parameter passed to the queue receive function specifies that
 * the task should be held in the Blocked state indefinitely to wait for data
 * to be available on the queue.  The queue receive task will only leave the
 * Blocked state when the queue send task writes to the queue.  As the queue
 * send task writes to the queue every 200 (simulated - see notes above)
 * milliseconds, the queue receive task leaves the Blocked state every 200
 * milliseconds, and therefore outputs a message every 200 milliseconds.
 */

/*-----------------------------------------------------------*/

/* Standard includes. */
#include "NWManager.h"
#include "Internal_Communication.h"
#include "CommonStructure.h"
#include "MyAppConfig.h"
#include "TokenValidator.h"
#include "AdminManager.h"
#include "ConfigManager.h"
#include "KeyManager.h"
#include "debug.h"

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/*-----------------------------------------------------------*/

/*
 * The tasks as described in the comments at the top of this file.
 */

/*-----------------------------------------------------------*/

//TODO pass queues & semaphores as parameters to tasks
//TODO pass keyring & domain as parameters to tasks ?

void main_myapp( void )
{
	QueueHandle_t xQueue_2AM    = NULL;    /* Queue TokenValidator 2 AdminManager. */
	QueueHandle_t xQueue_2IC    = NULL;    /* Queue TokenValidator or AdminManager 2 NetworkManager. */
	QueueHandle_t xQueue_2TV    = NULL;    /* Queue NW 2 TokenValidator. */
	QueueHandle_t xQueue_2CM    = NULL;    /* Queue AdminManager 2 ConfigManager. */
	QueueHandle_t xQueue_2KM    = NULL;
	QueueHandle_t xQueue_2NW    = NULL;
	QueueHandle_t xQueue_P2IC   = NULL;    /* Queue TokenValidator or AdminManager 2 NetworkManager. */

	void* Tab[7];
	/* Create the request queue. */
	xQueue_2TV  = xQueueCreate( mainQUEUE_LENGTH, sizeof( event_t ) );
	xQueue_2AM  = xQueueCreate( mainQUEUE_LENGTH, sizeof (event_t) );
	xQueue_2IC  = xQueueCreate( mainQUEUE_LENGTH, sizeof (event_t) );
	xQueue_P2IC  = xQueueCreate( mainQUEUE_LENGTH, sizeof (event_t) );
	xQueue_2CM  = xQueueCreate( mainQUEUE_LENGTH, sizeof (event_t) );
	xQueue_2KM  = xQueueCreate( mainQUEUE_LENGTH, sizeof (event_t) );
	xQueue_2NW  = xQueueCreate( mainQUEUE_LENGTH, sizeof (event_t) );
	xQueue_P2IC  = xQueueCreate( mainQUEUE_LENGTH, sizeof (event_t) );

	Tab[0] = xQueue_2AM ;
	Tab[1] = xQueue_2IC ;
	Tab[2] = xQueue_2TV ;
	Tab[3] = xQueue_2CM ;
	Tab[4] = xQueue_2KM ;
	Tab[5] = xQueue_2NW ;
	Tab[6] = xQueue_2IC ;


	if( xQueue_2TV != NULL
			&& xQueue_2CM != NULL
			&& xQueue_2KM != NULL
			&& xQueue_2IC != NULL
			&& xQueue_2AM   != NULL
			&& xQueue_2NW   != NULL
			&& xQueue_P2IC   != NULL
			)//TODO add tests for creation of all keys
	{

		xTaskCreate( NW_Task,
				     "Nx",
					 configMINIMAL_STACK_SIZE,
					 Tab,
					 IC_MANAGER_TASK_PRIORITY,
					 NULL );
		xTaskCreate( InternalCommunicationTask,
				     "Nx",
					 configMINIMAL_STACK_SIZE,
					 Tab,
					 IC_MANAGER_TASK_PRIORITY,
					 NULL );

		xTaskCreate( TokenValidateTask,					/* The function that implements the task. */
					"Tx", 									/* The text name assigned to the task - for debug only as it is not used by the kernel. */
					configMINIMAL_STACK_SIZE, 				/* The size of the stack to allocate to the task. */
					Tab,                                   /* The parameter passed to the task - just to check the functionality. */
					TOKEN_VALIDATE_TASK_PRIORITY, 		    /* The priority assigned to the task. */
					NULL );									/* The task handle is not required, so NULL is passed. */

		xTaskCreate( AdminManagerTask,
			         "Ax",
				     configMINIMAL_STACK_SIZE,
				     Tab,
				     ADMIN_MANAGER_TASK_PRIORITY,
					 NULL   );

		xTaskCreate( ConfigManagerTask,
			         "Cx",
				     configMINIMAL_STACK_SIZE,
				     Tab,
				     CONFIG_MANAGER_TASK_PRIORITY,
					 NULL   );

		xTaskCreate( KeyManagerTask,
			         "Kx",
				     configMINIMAL_STACK_SIZE,
				     Tab,
				     KEY_MANAGER_TASK_PRIORITY,
					 NULL   );

		/* Start the tasks and timer running. */
		vTaskStartScheduler();
	}

	/* If all is well, the scheduler will now be running, and the following
	line will never be reached.  If the following line does execute, then
	there was insufficient FreeRTOS heap memory available for the idle and/or
	timer tasks	to be created.  See the memory management section on the
	FreeRTOS web site for more details. */

	debug("I should not arrive here.\n");

	for( ;; );
}


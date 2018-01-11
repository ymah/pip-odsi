/*
 * NW_Manager.c
 *
 *  Created on: 14 déc. 2017
 *      Author: hzgf0437
 */



/* Standard includes. */
#include "CommonStructure.h"
#include "MyAppConfig.h"
#include "validateToken_Interface.h"
#include "ResponseCode.h"
#include "debug.h"
#include "string.h"
#include "structcopy.h"
/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/*-----------------------------------------------------------*/

void NW_Task( void *pvParameters )
{
	QueueHandle_t xQueue_2IC = ( (QueueHandle_t*) pvParameters)[1];
	SemaphoreHandle_t xSem_2IC = ( (SemaphoreHandle_t*) pvParameters)[5];


	TickType_t xNextWakeTime;

	event_t EventRequest;
	incomingMessage_t ValueToSend;
	incomingMessage_t VTS[12];

	const TickType_t xBlockTime = pdMS_TO_TICKS( NW_MANAGER_SEND_FREQUENCY_MS );

	event_t EventResponse;
	response_t MessageToReturn;

	char buffer[8*sizeof(int)];
	/* Remove compiler warning in the case that configASSERT() is not
	defined. */
	( void ) pvParameters;

	int i=0;

	/*Reset & Inititialize the messages to be sent*/
	for (i=0;i<12;i++){
		incomingMessagereset(&VTS[i]);
	}

	incomingMessageinit(&VTS[0], "20171214100001\0", "Dev1\0", "P1\0", "Friend\0","\0",READ_DOMID);
	incomingMessageinit(&VTS[1], "20171214100001\0", "Dev1\0", "P1\0", "Friend\0", DOM_ID_UPDATE, UPDATE_DOMID);
	incomingMessageinit(&VTS[2], "20171214100001\0", "Dev1\0", "P1\0", "Friend\0","\0", READ_DOMID);
	incomingMessageinit(&VTS[3], "20171214100001\0", "Dev1\0", "P1\0", "Pirate\0",DOM_ID_UPDATE, UPDATE_DOMID);
	incomingMessageinit(&VTS[4], "20171214100001\0", "Dev1\0", "P1\0", "Friend\0","1:\0",READ_KEY);
	incomingMessageinit(&VTS[5], "20171214100001\0", "Dev1\0", "P1\0", "Friend\0","2:",READ_KEY);
	incomingMessageinit(&VTS[6], "20171214100001\0", "Dev1\0", "P1\0", "Friend\0","2:18", ADD_KEY);
	incomingMessageinit(&VTS[7], "20171214100001\0", "Dev1\0", "P1\0", "Friend\0","2:", READ_KEY);
	incomingMessageinit(&VTS[8], "20171214100001\0", "Dev1\0", "P1\0", "Friend\0","2:", DELETE_KEY);
	incomingMessageinit(&VTS[9], "20171214100001\0", "Dev1\0", "P1\0", "Friend\0","2:",READ_KEY);
	incomingMessageinit(&VTS[10], "20171214100001\0", "Dev1\0", "P1\0", "Friend\0","1:18",UPDATE_KEY);
	incomingMessageinit(&VTS[11], "20171214100001\0", "Dev1\0", "P1\0", "Friend\0","1:",READ_KEY);

	/* Initialise xNextWakeTime - this only needs to be done once. */
	xNextWakeTime = xTaskGetTickCount();

	i=0;
	debug("NW Manager started\n");
	for( i=0;;i=(i+1)%12 )
	{
		debug("iteration ");
		debug(itoa(i,buffer,10));
		debug("\n");
		incomingMessagecpy(&ValueToSend,&VTS[i]);

		/* Place this task in the blocked state until it is time to run again.
		The block time is specified in ticks, the constant used converts ticks
		to ms.  While in the Blocked state this task will not consume any CPU
		time. */
		vTaskDelayUntil( &xNextWakeTime, xBlockTime );

	}

	EventRequest.eventType=INMESSAGE;
	incomingMessagecpy( &EventRequest.eventData.incomingMessage, &ValueToSend);
	xQueueSend( xQueue_2IC, &EventRequest, 0U );
	xSemaphoreGive(xSem_2IC);

	/* Receive Response data*/

}

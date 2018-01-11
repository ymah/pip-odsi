/*
 * routeCommandInterface.c
 *
 *  Created on: 20 nov. 2017
 *      Author: hzgf0437
 */

/*-----------------------------------------------------------*/

/* Standard includes. */

/*MyApp Config include*/
#include "CommonStructure.h"
#include "routeCommand_Interface.h"
#include "routeCommandSimple.h"

/*FreeRTOS include*/
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"


/*-----------------------------------------------------------*/

//extern QueueHandle_t xQueue_ConfigManager;/* Queue AdminManager 2 ConfigManager. */


/*-----------------------------------------------------------*/

int routeCommand(event_t ReceivedValue, QueueHandle_t xQueue_AM2CM, QueueHandle_t xQueue_AM2KM){
	int result;
	result = routeCommandSimple( ReceivedValue, xQueue_AM2CM, xQueue_AM2KM);
	return result;
}

/*-----------------------------------------------------------*/

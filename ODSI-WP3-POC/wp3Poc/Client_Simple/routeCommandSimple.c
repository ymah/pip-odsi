/*
 * routeCommandSimple.c
 *
 *  Created on: 20 nov. 2017
 *      Author: hzgf0437
 */

/* Standard includes. */
//#include <stdio.h>
#include "CommonStructure.h"
#include "routeCommandSimple.h"
#include "ResponseCode.h"
#include "debug.h"
#include "structcopy.h"
#include "stdint.h"

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/*-----------------------------------------------------------*/

//extern QueueHandle_t xQueue_AM2CM;/* Queue AdminManager 2 ConfigManager. */
//extern QueueHandle_t xQueue_AM2KM;/* Queue AdminManager 2 KeyManager. */

/*-----------------------------------------------------------*/

uint32_t routeCommandSimple(event_t ReceivedValue, QueueHandle_t xQ_2CM, QueueHandle_t xQ_2KM){
	QueueHandle_t xQueue_AM2CM = xQ_2CM;
	QueueHandle_t xQueue_AM2KM = xQ_2KM;
	event_t ValueToSend;
	/*Identify the target of command
	 */
	eventcpy( &ValueToSend, &ReceivedValue);

	switch(ReceivedValue.eventData.command.instruction){
	case READ_DOMID :
	case UPDATE_DOMID :
	case CREATE_DOM :
		DEBUG(TRACE,"call config manager\n");
		xQueueSend( xQueue_AM2CM, &ValueToSend, 0U );
		return SUCCESS;
		break;
	case ADD_KEY:
	case READ_KEY:
	case UPDATE_KEY:
	case DELETE_KEY:
		DEBUG(TRACE,"call key ring manager\n");
		xQueueSend( xQueue_AM2KM, &ValueToSend, 0U );
		return SUCCESS;
		break;
	default:
		return UNKNOWN_COMMAND;
		break;
	}
}

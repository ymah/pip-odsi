/*
 * AdminManagaer.c
 *
 *  Created on: 19 nov. 2017
 *      Author: HZGF0437
 */

/*-----------------------------------------------------------*/

/* Standard includes. */
#include "CommonStructure.h"
#include "routeCommand_Interface.h"
#include "debug.h"
#include "structcopy.h"
#include "ResponseCode.h"

/*FreeRTOS include*/
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/*-----------------------------------------------------------*/


void AdminManagerTask( void *pvParameters ){
	QueueHandle_t xQueue_2AM = ( (QueueHandle_t*) pvParameters)[0];
	QueueHandle_t xQueue_2IC = ( (QueueHandle_t*) pvParameters)[1];
	QueueHandle_t xQueue_2TV = ( (QueueHandle_t*) pvParameters)[2];
	QueueHandle_t xQueue_AM2CM = ( (QueueHandle_t*) pvParameters)[3];
	QueueHandle_t xQueue_AM2KM = ( (QueueHandle_t*) pvParameters)[4];

	event_t ValueToSend;
	event_t ReceivedEvent;
	event_t TokenRequest;
	event_t EventToSend;
	event_t TokenResponse;

	/* Remove compiler warning in the case that configASSERT() is not
		defined.*/
	( void ) pvParameters;

	for( ;; )
	{
		/* Wait until something arrives in the queue - this task will block
			indefinitely provided INCLUDE_vTaskSuspend is set to 1 in
			FreeRTOSConfig.h. */

		xQueueReceive( xQueue_2AM, &ReceivedEvent, portMAX_DELAY );
		/*Identify the target of command
		 */

		switch(ReceivedEvent.eventType){
		case INMESSAGE:
			DEBUG(TRACE,"Sending command to token validator\n");
			eventcpy( &TokenRequest , &ReceivedEvent );
			xQueueSend( xQueue_2TV, &TokenRequest, 0U );

			//Receive Response from token validator
			xQueueReceive( xQueue_2AM, &TokenResponse, portMAX_DELAY );

			if (TokenResponse.eventType == RESPONSE && TokenResponse.eventData.response.responsecode == SUCCESS){
				DEBUG(TRACE,"Sending command to destination\n");
				commandcpy( &ValueToSend.eventData.command , &ReceivedEvent.eventData.incomingMessage.command );
				ValueToSend.eventType=COMMAND;
				routeCommand( ValueToSend, xQueue_AM2CM, xQueue_AM2KM);
			}
			else{
				DEBUG(TRACE,"Sending response\n");
				eventcpy(&EventToSend, &TokenResponse);
				xQueueSend( xQueue_2IC, &EventToSend, 0U );
			}
			break;
		case COMMAND:
			DEBUG(TRACE,"AdminManager: COMMAND Event Type not supported\n");
			break;
		case RESPONSE:
			DEBUG(TRACE,"Proceeding response\n");
			eventcpy( &EventToSend , &ReceivedEvent );
			xQueueSend( xQueue_2IC, &EventToSend, 0U );
			break;
		default:
			DEBUG(TRACE,"AdminManager: Unknown Event Type\n");
			break;
		}

	}

}
/*-----------------------------------------------------------*/

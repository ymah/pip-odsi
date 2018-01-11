/*
 * TokenValidator.c
 *
 *  Created on: 19 nov. 2017
 *      Author: HZGF0437
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
void TokenValidateTask( void *pvParameters )
{
	QueueHandle_t xQueue_2AM = ( (QueueHandle_t*) pvParameters)[0];
	QueueHandle_t xQueue_2TV = ( (QueueHandle_t*) pvParameters)[2];
	QueueHandle_t xQueue_2KM = ( (QueueHandle_t*) pvParameters)[4];

	event_t ReceivedValue;
	response_t ResponseToSend;
	event_t EventToSend;
	event_t KeyRequest;
	event_t KeyResponse;
	char result;

	/* Remove compiler warning in the case that configASSERT() is not
	defined. */
	( void ) pvParameters;

	for( ;; )
	{
		/* Wait until something arrives in the queue - this task will block
		indefinitely provided INCLUDE_vTaskSuspend is set to 1 in
		FreeRTOSConfig.h. */
		//xSemaphoreTake( xSem_2TV, portMAX_DELAY );
		xQueueReceive( xQueue_2TV, &ReceivedValue, portMAX_DELAY );
		debug("Hello! I am the token Validator !\n");

		switch(ReceivedValue.eventType){
		case INMESSAGE:
			KeyRequest.eventType=GET_KEY;
			incomingMessagecpy(&KeyRequest.eventData.incomingMessage, &ReceivedValue.eventData.incomingMessage);

			/*Create a command to request the key value*/
			KeyRequest.eventData.command.instruction=READ_KEY;
			strcpy( KeyRequest.eventData.command.data , "1:" );

			xQueueSend( xQueue_2KM, &KeyRequest, 0U );

			xQueueReceive( xQueue_2TV, &KeyResponse, portMAX_DELAY );

			/*Validate the token received */

			result=token_validate(ReceivedValue.eventData.incomingMessage.token, KeyResponse.eventData.response.data);

			/* Send to the queue - causing the Administration Manager to unblock,
			 * send the command to the expected target for processing
			 * 0 is used as the block time so the sending operation
			 * will not block - it shouldn't need to block as the queue should always
			 * be empty at this point in the code. */

			if(result == 1){
				debug("Token is valid\n");
				EventToSend.eventType=RESPONSE;
				EventToSend.eventData.incomingMessage.userID=ResponseToSend.userID;
				ResponseToSend.responsecode= SUCCESS ;

				EventToSend.eventData.response=ResponseToSend;

				xQueueSend( xQueue_2AM, &EventToSend, 0U );
			}
			else{
				debug("Token is not valid\n");
				ResponseToSend.userID=ReceivedValue.eventData.incomingMessage.userID;
				strcpy(ResponseToSend.data, "");
				ResponseToSend.responsecode= INVALID_TOKEN ;

				EventToSend.eventType=RESPONSE;
				EventToSend.eventData.response=ResponseToSend;

				xQueueSend( xQueue_2AM, &EventToSend, 0U );
			}
			break;
		case COMMAND :
		case RESPONSE :
		case GET_KEY :
		default :
			debug("TOKEN_VALIDATOR: Unknown Event Type\n");
			break;
		}
	}
}

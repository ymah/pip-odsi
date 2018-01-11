/*
 * KeyManager.c
 *
 *  Created on: 21 nov. 2017
 *      Author: hzgf0437
 */


/* Standard includes. */
#include "CommonStructure.h"
#include "ManageKey_Interface.h"
#include "MyAppConfig.h"
#include "string.h"
#include "debug.h"
#include "structcopy.h"
#include "responsecode.h"
#include "stdint.h"

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/*-----------------------------------------------------------*/

void KeyManagerTask( void *pvParameters ){
	QueueHandle_t xQueue_2AM = ( (QueueHandle_t*) pvParameters)[0];
	QueueHandle_t xQueue_2TV = ( (QueueHandle_t*) pvParameters)[2];
	QueueHandle_t xQueue_2KM = ( (QueueHandle_t*) pvParameters)[4];

	char buffer[8*sizeof(uint32_t)];
	event_t ReceivedValue;
	char responseData[DATA_SIZE]={};
	uint32_t result;
	event_t EventToSend;
	response_t ResponseToSend;

	/* Initiatilize token key. This part may not be necessary in an implementation where the keys are stored in a file or a DB*/
	key_t * List_TokenKey=NULL;

	debug("Initialize Token Key List\n");

	command_t InitValue={0,ADD_KEY,"1:17"};
	ManageKey(InitValue, &List_TokenKey, NULL);

	/* Remove compiler warning in the case that configASSERT() is not
	defined.*/
	( void ) pvParameters;


	for( ;; )
	{
		buffer[0]='\0';
		eventreset(&ReceivedValue);
		result=0;
		strcpy(responseData,"\0");
		eventreset(&EventToSend);
		responsereset(&ResponseToSend);

		/* Wait until something arrives in the queue - this task will block
		indefinitely provided INCLUDE_vTaskSuspend is set to 1 in
		FreeRTOSConfig.h. */
		xQueueReceive( xQueue_2KM, &ReceivedValue, portMAX_DELAY );
		debug("Hello! I am the Key Manager !\n");

		switch(ReceivedValue.eventType){
		case GET_KEY:
			result = ManageKey(ReceivedValue.eventData.command, &List_TokenKey, responseData);
			debug("Get key for token validation: Result : ");
			debug(itoa(result,buffer,16));
			debug(" and data: ");
			debug(responseData);
			debug("\n");

			ResponseToSend.userID = ReceivedValue.eventData.command.userID;
			strcpy(ResponseToSend.data,responseData);
			ResponseToSend.responsecode= result ;

			EventToSend.eventType=RESPONSE;
			EventToSend.eventData.response=ResponseToSend;

			xQueueSend( xQueue_2TV, &EventToSend, 0U );
			break;
		case COMMAND:
			result = ManageKey(ReceivedValue.eventData.command, &List_TokenKey, responseData);

			debug("Manage Key: Result : ");
			debug(itoa(result,buffer,16));
			debug(" and data: ");
			debug(responseData);
			debug("\n");

			ResponseToSend.userID = ReceivedValue.eventData.command.userID;
			strcpy(ResponseToSend.data,responseData);
			ResponseToSend.responsecode= result ;

			EventToSend.eventType=RESPONSE;
			EventToSend.eventData.response=ResponseToSend;

			xQueueSend( xQueue_2AM, &EventToSend, 0U );
			break;
		case INMESSAGE :
		case RESPONSE :
		default :
			debug("KeyManager: Unknown Event Type\n");
			break;
		}
	}

}

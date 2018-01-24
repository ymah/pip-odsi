/*
 * ConfigManager.c
 *
 *  Created on: 20 nov. 2017
 *      Author: hzgf0437
 */


/* Standard includes. */
#include "CommonStructure.h"
#include "ManageDomain_Interface.h"
#include "MyAppConfig.h"
#include "debug.h"
#include "string.h"
#include "structcopy.h"
#include "stdint.h"

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/*-----------------------------------------------------------*/

void ConfigManagerTask( void *pvParameters ){
	QueueHandle_t xQueue_2AM = ( (QueueHandle_t*) pvParameters)[0];
	QueueHandle_t xQueue_2CM = ( (QueueHandle_t*) pvParameters)[3];

	char responseData[100]={};
	event_t EventToSend;
	response_t ResponseToSend;
	event_t ReceivedValue;

	/*Initialize current domain*/
	domain_t CurrentDomain;
	strcpy(CurrentDomain.DomId,DOM_ID_OWNER);
	CurrentDomain.nbChilDom=NB_CHILD_DOM_DEFAULT;

	/* Remove compiler warning in the case that configASSERT() is not
	defined.*/
	( void ) pvParameters;

	for( ;; )
	{
		responseData[0]='\0';
		eventreset(&EventToSend);
		responsereset(&ResponseToSend);
		eventreset(&ReceivedValue);

		/* Wait until something arrives in the queue - this task will block
		indefinitely provided INCLUDE_vTaskSuspend is set to 1 in
		FreeRTOSConfig.h. */
		xQueueReceive( xQueue_2CM, &ReceivedValue, portMAX_DELAY );

		DEBUG(TRACE,"Config Manager !\n");

		ResponseToSend.responsecode=ManageDomain(ReceivedValue,&CurrentDomain,responseData);

		if(responseData[0] != '\0')
			strcpy(ResponseToSend.data,responseData);

		ResponseToSend.userID = ReceivedValue.eventData.command.userID;

		EventToSend.eventType=RESPONSE;
		EventToSend.eventData.response=ResponseToSend;
		xQueueSend( xQueue_2AM, &EventToSend, 0U );

		DEBUG(TRACE,"Config-Response code: %#04X, Data: %s\n", ResponseToSend.responsecode, ResponseToSend.data);
	}

}

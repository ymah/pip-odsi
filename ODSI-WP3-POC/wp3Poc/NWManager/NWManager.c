/*
 * NWManager.c
 *
 *  Created on: 18 déc. 2017
 *      Author: HZGF0437
 */


/* Standard includes. */
#include "CommonStructure.h"
#include "MyAppConfig.h"
#include "ResponseCode.h"
#include "debug.h"
#include "mystdlib.h"
#include "string.h"
#include "structcopy.h"
#include "parser.h"
#include "NWManager.h"
#include "NWManager_Interface.h"
/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"


void NW_Task( void *pvParameters )
{
	QueueHandle_t xQueue_2IC = ( (QueueHandle_t*) pvParameters)[6];
	QueueHandle_t xQueue_2NW = ( (QueueHandle_t*) pvParameters)[5];

	event_t ICEvent;
	event_t EventRequest;
	char InValue[IN_MAX_MESSAGE_SIZE]={};
	char OutValue[OUT_MAX_MESSAGE_SIZE]={};

	uint32_t size_in=0, sizeout=0, l_result=1;

	void* ServerSocket;
	void* ClientSocket;

	ServerSocket=initialize();
	l_result=ext_listen( ServerSocket);
	if (l_result ==1 ){
		DEBUG(INFO, "Error when listening\n");
	}

	for(;;){
		ClientSocket=get_connection(ServerSocket);

		mymemset(InValue, 0, IN_MAX_MESSAGE_SIZE*sizeof(char));
		size_in=ext_receive(ClientSocket, InValue);

		EventRequest.eventType=NW_IN;
		mymemcpy(&EventRequest.eventData.nw.stream, InValue, size_in);
		EventRequest.eventData.nw.size=size_in;

		xQueueSend( xQueue_2IC, &EventRequest, 0U );

		/* Receive Response data*/
		xQueueReceive( xQueue_2NW, &ICEvent, portMAX_DELAY );

		if(ICEvent.eventType == NW_OUT){
			sizeout=ICEvent.eventData.nw.size;
			mymemcpy(OutValue, ICEvent.eventData.nw.stream, sizeout);
			ext_send(ClientSocket, OutValue, sizeout);
		}

		mycloseSocket(ClientSocket);
	}





}

/*
 * Communicate_SimpleAdaptor.c
 *
 *  Created on: 21 déc. 2017
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
#include "parser.h"
#include "stdint.h"

#include "InternalCommunication_Interface.h"
#include "communicateSimple.h"

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"


event_t myreceive(char* data, QueueHandle_t xQueue_P2IC){
	uint32_t result;
	event_t EventToReturn;

	eventreset(&EventToReturn);
	result=receive_simple(data, xQueue_P2IC);
	if (result != 0){
		EventToReturn.eventData.incomingMessage=deserialize_incomingMessage(data, result);
		EventToReturn.eventType=INMESSAGE;

		return EventToReturn;
	}
	else
		return EventToReturn;
}

void mysend (uint32_t dest, char* data, QueueHandle_t xQueue_IC2P, uint32_t datasize){
	send_simple(data, xQueue_IC2P, datasize);
}

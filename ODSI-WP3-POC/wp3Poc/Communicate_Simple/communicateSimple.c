/*
 * communicateSimple.c
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

#include "CommunicateSimple.h"

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/**
 *
 * @param data
 * @param xQueue_P2IC
 * @returnsize of the stream received
 */
uint32_t receive_simple(char* data, QueueHandle_t xQueue_P2IC){

	event_t Event;
	xQueueReceive( xQueue_P2IC, &Event, portMAX_DELAY ); //receive(data, src)
	switch(Event.eventType){
	case NW_IN:
		memset(data, 0, IN_MAX_MESSAGE_SIZE);
		debug("Internal Communication received a message\n");
		memcpy(data, Event.eventData.nw.stream, Event.eventData.nw.size);
		return Event.eventData.nw.size;
	default:
		return GENERAL_ERROR;
	}
}

void send_simple(char* data, QueueHandle_t xQueue_IC2P, uint32_t datasize){
	event_t Event;
	Event.eventType=NW_OUT;
	memcpy(Event.eventData.nw.stream, data, datasize);
	Event.eventData.nw.size=datasize;

	xQueueSend( xQueue_IC2P, &Event, 0U ); //send(dest, data)
}


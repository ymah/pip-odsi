/*
 * manageNW_simple.c
 *
 *  Created on: 14 déc. 2017
 *      Author: hzgf0437
 */


/* Standard includes. */
#include "CommonStructure.h"
#include "MyAppConfig.h"
#include "ResponseCode.h"
#include "debug.h"
#include "string.h"
#include "structcopy.h"
#include "parser.h"
#include "NWManager_Interface.h"
#include "stdint.h"
/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/*-----------------------------------------------------------*/
uint32_t iteration=0;

/*-----------------------------------------------------------*/

void* initialize(){

	return NULL;
}


void* get_connection(void* ListenSocket){

	return NULL;
}

uint32_t ext_listen(void* ClientSocket, char* data)
{

	TickType_t xNextWakeTime;
	incomingMessage_t VTS[12];
	//incomingMessage_t Check;

	const TickType_t xBlockTime = pdMS_TO_TICKS( NW_MANAGER_SEND_FREQUENCY_MS );

	//event_t EventResponse;
	//response_t MessageToReturn;

	char buffer[8*sizeof(uint32_t)];

	uint32_t i=0;
	uint32_t size=0;

	/*Reset & Inititialize the messages to be sent*/
	for (i=0;i<12;i++){
		incomingMessagereset(&VTS[i]);
	}

	incomingMessageinit(&VTS[0], 1, 1, 1, "Friend\0","\0",READ_DOMID);
	incomingMessageinit(&VTS[1], 1, 1, 1, "Friend\0", DOM_ID_UPDATE, UPDATE_DOMID);
	incomingMessageinit(&VTS[2], 1, 1, 1, "Friend\0","\0", READ_DOMID);
	incomingMessageinit(&VTS[3], 1, 1, 1, "Pirate\0",DOM_ID_UPDATE, UPDATE_DOMID);
	incomingMessageinit(&VTS[4], 1, 1, 1, "Friend\0","1:\0",READ_KEY);
	incomingMessageinit(&VTS[5], 1, 1, 1, "Friend\0","2:",READ_KEY);
	incomingMessageinit(&VTS[6], 1, 1, 1, "Friend\0","2:18", ADD_KEY);
	incomingMessageinit(&VTS[7], 1, 1, 1, "Friend\0","2:", READ_KEY);
	incomingMessageinit(&VTS[8], 1, 1, 1, "Friend\0","2:", DELETE_KEY);
	incomingMessageinit(&VTS[9], 1, 1, 1, "Friend\0","2:",READ_KEY);
	incomingMessageinit(&VTS[10], 1, 1, 1, "Friend\0","1:18",UPDATE_KEY);
	incomingMessageinit(&VTS[11], 1, 1, 1, "Friend\0","1:",READ_KEY);

	/* Initialise xNextWakeTime - this only needs to be done once. */
	xNextWakeTime = xTaskGetTickCount();

	debug("NW Manager started\n");

	debug("iteration ");
	debug(itoa(iteration,buffer,10));
	debug("\n");

	size=serialize_incomingMessage(VTS[iteration], data);
	//Check=deserialize_incomingMessage(data, size);

	/*debug("Command Data: ");
	debug(Check.command.data);
	debug("\n");
	debug("Token: ");
	debug(Check.token);
	debug("\n");*/

	iteration=(iteration+1)%12 ;

	/* Place this task in the blocked state until it is time to run again.
		The block time is specified in ticks, the constant used converts ticks
		to ms.  While in the Blocked state this task will not consume any CPU
		time. */
	vTaskDelayUntil( &xNextWakeTime, xBlockTime );
	return size;
}

void ext_send(void* ClientSocket, char* outData, uint32_t size){
	response_t response;
	char buffer[8*sizeof(uint32_t)];

	response=deserialize_response(outData, size);

	debug("NW-Response code: ");
	debug(itoa(response.responsecode,buffer,16));
	debug(" and data: ");
	debug(response.data);
	debug("\n\n");
}

void close(void* Socket){

}

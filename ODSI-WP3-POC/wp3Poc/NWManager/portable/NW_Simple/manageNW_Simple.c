/*
 * manageNW_simple.c
 *
 *  Created on: 14 déc. 2017
 *      Author: hzgf0437
 */

#include <stdio.h>

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

uint32_t ext_listen( void* LSocket){
	return 0;
}

uint32_t ext_receive(void* ClientSocket, char* data)
{

	TickType_t xNextWakeTime;
	incomingMessage_t VTS[12];
	incomingMessage_t Check;

	const TickType_t xBlockTime = pdMS_TO_TICKS( NW_MANAGER_SEND_FREQUENCY_MS );

	//event_t EventResponse;
	//response_t MessageToReturn;

	char token_f[TOKEN_SIZE];
	char token_p[TOKEN_SIZE];

	uint32_t i,j=0;
	uint32_t size=0;

	for(j=0;j<TOKEN_SIZE;j++){
		token_f[j]=0xff;
		token_p[j]=0x00;
	}
	DEBUG(INFO, "VALID TOKEN: %X\n", token_f);
	DEBUG(INFO, "INVALID TOKEN: %X\n", token_p);
	/*Reset & Inititialize the messages to be sent*/
	for (i=0;i<12;i++){
		incomingMessagereset(&VTS[i]);
	}



	incomingMessageinit(&VTS[0], 1, 1, 1, TOKEN_SIZE, token_f,"\0",READ_DOMID);
	incomingMessageinit(&VTS[1], 1, 1, 1, TOKEN_SIZE, token_f, DOM_ID_UPDATE, UPDATE_DOMID);
	incomingMessageinit(&VTS[2], 1, 1, 1,TOKEN_SIZE, token_f,"\0", READ_DOMID);
	incomingMessageinit(&VTS[3], 1, 1, 1,TOKEN_SIZE, token_p, DOM_ID_UPDATE, UPDATE_DOMID);
	incomingMessageinit(&VTS[4], 1, 1, 1,TOKEN_SIZE, token_f,"1:\0",READ_KEY);
	incomingMessageinit(&VTS[5], 1, 1, 1,TOKEN_SIZE, token_f,"2:",READ_KEY);
	incomingMessageinit(&VTS[6], 1, 1, 1,TOKEN_SIZE, token_f,"2:18", ADD_KEY);
	incomingMessageinit(&VTS[7], 1, 1, 1,TOKEN_SIZE, token_f,"2:", READ_KEY);
	incomingMessageinit(&VTS[8], 1, 1, 1,TOKEN_SIZE, token_f,"2:", DELETE_KEY);
	incomingMessageinit(&VTS[9], 1, 1, 1,TOKEN_SIZE, token_f,"2:",READ_KEY);
	incomingMessageinit(&VTS[10], 1, 1, 1,TOKEN_SIZE, token_f,"1:18",UPDATE_KEY);
	incomingMessageinit(&VTS[11], 1, 1, 1,TOKEN_SIZE, token_f,"1:",READ_KEY);


	/* Initialise xNextWakeTime - this only needs to be done once. */
	xNextWakeTime = xTaskGetTickCount();

	DEBUG(TRACE,"NW Manager started\n");

	DEBUG(INFO,"iteration %lu\n", iteration);

	size=serialize_incomingMessage(VTS[iteration], data);

	Check=deserialize_incomingMessage(data, size);
	DEBUG(TRACE,"UserID: %lu, DeviceID: %lu, DomainID: %lu, Instructin: %lu, Command Data: %s, Token: %X, \n", Check.userID, Check.deviceID, Check.domainID, Check.command.instruction, Check.command.data, Check.token);

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

	response=deserialize_response(outData, size);

	DEBUG(INFO,"Response code: %04X Data : %s \n\n", response.responsecode, response.data);
}

void mycloseSocket(void* Socket){

}

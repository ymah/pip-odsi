/*
 * parser.c
 *
 *  Created on: 14 déc. 2017
 *      Author: hzgf0437
 */

#include "CommonStructure.h"
#include "string.h"
#include "debug.h"
#include "structcopy.h"
#include "stdint.h"
#include "mystdlib.h"
#include "parser.h"
#include "ResponseCode.h"
#include <stdarg.h>

uint32_t myhtonl(uint32_t hostlong){
	return hostlong;
}

uint32_t myntohl(uint32_t netlong){
	return netlong;
}

uint32_t serialize_incomingMessage(incomingMessage_t message, char* data){
	data[0]='\0';
	uint32_t size_total;
	uint32_t size_data;
	char* p=data;
	uint32_t ID;

	DEBUG(TRACE,"%s\n","Serialize your message.");

	size_data=strlen(message.command.data);

	size_total=sizeof(message.userID)
						+sizeof(message.deviceID)
						+sizeof(message.domainID)
						+sizeof(message.command.instruction)
						+sizeof(size_data)
						+size_data
						+sizeof(message.tokenSize)
						+message.tokenSize;


	if (size_total <= IN_MAX_MESSAGE_SIZE){
		ID=myhtonl(message.userID);
		mymemcpy(p, &ID, sizeof(ID));
		p += sizeof(ID);

		ID=myhtonl(message.deviceID);
		mymemcpy(p, &ID, sizeof(ID));
		p += sizeof(ID);

		ID=myhtonl(message.domainID);
		mymemcpy(p, &ID, sizeof(ID));
		p += sizeof(ID);

		ID=myhtonl(message.command.instruction);
		mymemcpy(p, &ID, sizeof(ID));
		p += sizeof(ID);

		ID=myhtonl(size_data);
		mymemcpy(p, &ID, sizeof(ID));
		p += sizeof(ID);

		mymemcpy(p, message.command.data, size_data);
		p += size_data;

		ID=myhtonl(message.tokenSize);
		mymemcpy(p, &ID, sizeof(ID));
		p += sizeof(ID);

		mymemcpy(p, message.token, message.tokenSize);
		p += message.tokenSize ;

		DEBUG(TRACE,"Serialization completed\n");
		return size_total;
	}
	else {
		DEBUG(INFO,"ERROR\n");
		return GENERAL_ERROR;
	}

}

uint32_t serialize_response(response_t response, char* data){
	data[0]='\0';
	uint32_t size_total;
	uint32_t size_data=strlen(response.data);
	char* p=data;
	uint32_t ID;

	DEBUG(TRACE,"Serializing response.\n");

	size_total=sizeof(response.userID) + sizeof(response.responsecode) + size_data;
	//debug("Total length is");
	//debug( itoa(total_len, debug_buffer, 10) );
	//debug("\n");


	if (size_total <= OUT_MAX_MESSAGE_SIZE){
		ID=myhtonl(response.userID);
		mymemcpy(p, &ID, sizeof(ID));
		p += sizeof(ID);

		ID=myhtonl(response.responsecode);
		mymemcpy(p, &ID, sizeof(ID));
		p += sizeof(ID);

		mymemcpy(p, response.data, size_data);
		p += size_data;

		DEBUG(TRACE,"Serialization of response completed\n");
		return size_total;
	}
	else {
		DEBUG(INFO,"ERROR\n");
		return GENERAL_ERROR;
	}

}


incomingMessage_t deserialize_incomingMessage(char* data, uint32_t size_total){

	incomingMessage_t message;

	uint32_t size_data;

	incomingMessagereset(&message);

	uint32_t ID;
	char header[HEADER_SIZE	];

	if( size_total < IN_MAX_MESSAGE_SIZE){
		DEBUG(TRACE,"Deserializing message\n");
		mymemcpy(&header, data, HEADER_SIZE	);
		if(header[0] == "O" && header[1] == "D" && header[2] == "S" && header[3] == "I")
		data += sizeof(HEADER_SIZE);

		mymemcpy(&ID, data, sizeof(ID));
		message.userID=myntohl(ID);
		message.command.userID=myntohl(ID);
		data += sizeof(ID);

		mymemcpy(&ID, data, sizeof(ID));
		message.deviceID=myntohl(ID);
		data += sizeof(ID);

		mymemcpy(&ID, data, sizeof(ID));
		message.domainID=myntohl(ID);
		data += sizeof(ID);

		mymemcpy(&ID, data, sizeof(ID));
		message.command.instruction=myntohl(ID);
		data += sizeof(ID);

		mymemcpy(&ID, data, sizeof(ID));
		size_data=myntohl(ID);
		data += sizeof(ID);

		mymemcpy(message.command.data, data, size_data);
		data += size_data;

		mymemcpy(&ID, data, sizeof(ID));
		message.tokenSize=myntohl(ID);
		data += sizeof(ID);

		mymemcpy(message.token, data, message.tokenSize);
		data += message.tokenSize;

	}	else {
		DEBUG(INFO,"ERROR\n");
	}
	return message;
}


response_t deserialize_response(char* data, uint32_t size_total){

	response_t response;

	uint32_t size_data;
	uint32_t ID;

	responsereset(&response);

	if( size_total < OUT_MAX_MESSAGE_SIZE){
		DEBUG(TRACE,"Deserializing response\n");
		mymemcpy(&ID, data, sizeof(ID));
		response.userID=myntohl(ID);
		data += sizeof(ID);

		mymemcpy(&ID, data, sizeof(ID));
		response.responsecode=myntohl(ID);
		data += sizeof(ID);

		size_data = size_total - ( 2*sizeof(ID) );
		mymemcpy(&(response.data), data, size_data);
		data += size_data;
	}
	else {
		DEBUG(INFO,"ERROR\n");
	}
	return response;
}


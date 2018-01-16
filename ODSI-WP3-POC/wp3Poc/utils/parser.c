/*
 * parser.c
 *
 *  Created on: 14 d�c. 2017
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
	uint32_t size_token;
	char* p=data;
	uint32_t ID;

	debug("I am the parser. I will serialize your message.\n");

	size_data=strlen(message.command.data);
	size_token=strlen(message.token);

	size_total=sizeof(message.userID)
						+sizeof(message.deviceID)
						+sizeof(message.domainID)
						+sizeof(message.command.instruction)
						+sizeof(uint32_t) //size of data length
						+size_data
						+sizeof(uint32_t) //size of token length
						+size_token;


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

		ID=myhtonl(size_token);
		mymemcpy(p, &ID, sizeof(ID));
		p += sizeof(ID);

		mymemcpy(p, message.token, size_token);
		p += size_token ;


		debug("Serialization completed\n");
		return size_total;
	}
	else {
		debug("ERROR");
		return GENERAL_ERROR;
	}

}

uint32_t serialize_response(response_t response, char* data){
	data[0]='\0';
	uint32_t size_total;
	uint32_t size_data=strlen(response.data);
	char* p=data;
	uint32_t ID;

	//debug("I am the parser. I will serialize your response.\n");

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

		//debug("Serialization completed\n");
		return size_total;
	}
	else {
		debug("ERROR");
		return GENERAL_ERROR;
	}

}


incomingMessage_t deserialize_incomingMessage(char* data, uint32_t size_total){

	incomingMessage_t message;

	uint32_t size_token;
	uint32_t size_data;

	incomingMessagereset(&message);

	uint32_t ID;

	if( size_total < IN_MAX_MESSAGE_SIZE){
		//debug("I am the parser. I will deserialize your message\n");
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

		mymemcpy(&(message.command.data), data, size_data);
		data += size_data;

		mymemcpy(&ID, data, sizeof(ID));
		size_token=myntohl(ID);
		data += sizeof(ID);

		mymemcpy(&(message.token), data, size_token);
		data += size_token;

	}
	return message;
}


response_t deserialize_response(char* data, uint32_t size_total){

	response_t response;

	uint32_t size_data;
	uint32_t ID;

	responsereset(&response);

	if( size_total < OUT_MAX_MESSAGE_SIZE){
		//debug("I am the parser. I will deserialize your response\n");
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
	return response;
}


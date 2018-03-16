/*
 * manageNW_simple.c
 *
 *  Created on: 14 déc. 2017
 *      Author: hzgf0437
 */

#undef UNICODE
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0501


// Need to link with Ws2_32.lib
//#pragma comment (lib, "Ws2_32.lib")//normally done in the makefile
// #pragma comment (lib, "Mswsock.lib")

/* Windows includes */
#include <windows.h>
#include <winsock2.h>
#include <stddef.h>
#include <ws2tcpip.h>
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
#include "mystdlib.h"
#include <stdlib.h>
/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/*-----------------------------------------------------------*/

void* initialize(){
	WSADATA wsaData;
	uint32_t iResult;
	SOCKET* LSocket;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != 0) {
		DEBUG(INFO,"WSAStartup failed with error: %d\n", iResult);
		return NULL;
	}
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(DEFAULT_IP, DEFAULT_PORT, &hints, &result);
	if ( iResult != 0 ) {
		DEBUG(INFO,"getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return NULL;
	}
	// Create a SOCKET for connecting to server
	LSocket = (SOCKET*) calloc(1,sizeof(SOCKET));
	*LSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (*LSocket == INVALID_SOCKET) {
		DEBUG(INFO,"socket failed with error: %i\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return NULL;
	}

	// Setup the TCP listening socket
	iResult = bind( *LSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		DEBUG(INFO,"bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(*LSocket);
		WSACleanup();
		return NULL;
	}

	//freeaddrinfo(result);
	return LSocket;
}


uint32_t ext_listen( void* LSocket){
	uint32_t iResult = 0;
	iResult = listen(*(SOCKET*)LSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		DEBUG(INFO,"listen failed with error: %d\n", WSAGetLastError());
		closesocket(*(SOCKET*)LSocket);
		WSACleanup();
		return 1;
	}
	return 0;
}


void* get_connection(void* ListenSocket){
	// Accept a client socket
	SOCKET* CSocket=NULL;
	CSocket = (SOCKET*) calloc(1,sizeof(SOCKET));
	*CSocket = accept(*(SOCKET*)ListenSocket, NULL, NULL);

	if (*(SOCKET*)CSocket == INVALID_SOCKET) {
		DEBUG(INFO,"accept failed with error: %d\n", WSAGetLastError());
		closesocket(*(SOCKET*)ListenSocket);
		WSACleanup();
		return NULL;
	}

	return CSocket;
}

uint32_t ext_receive(void* ClientSocket, char* data){
	uint32_t iResult=0;
	uint32_t i=0;
	uint32_t recvbuflen1 = 4;
	uint32_t recvbuflen2;

		//Receive the first message with the size of the data to be received
		iResult = recv(*(SOCKET*)ClientSocket, data, recvbuflen1, 0);
		recvbuflen2=*((int*)data);
		DEBUG(TRACE,"length to read: %lu", recvbuflen2);
		//Receive the second message of size
		iResult = recv(*(SOCKET*)ClientSocket, data, recvbuflen2, 0);

		if (iResult > 0) {
			DEBUG(INFO,"Bytes received: %lu\n", iResult);
			DEBUG(TRACE,"Buffer content : %s\n", data);
			DEBUG(INFO,"Buffer content:");
			for (i=0;i<recvbuflen2;i++){
				debug1("%02X",data[i]);
			}
			debug1("\n");

		}
		else if (iResult == 0){
			DEBUG(INFO,"Connection closing...\n");
		}
		else  {
			DEBUG(INFO,"recv failed with error: %d\n", WSAGetLastError());
			closesocket(*(SOCKET*)ClientSocket);
			WSACleanup();
			return 1;
		}

	return recvbuflen2;
}


void ext_send(void* ClientSocket, char* outData, uint32_t size){
	uint32_t iSendResult=0;
	uint32_t i=0;

	iSendResult=send( *(SOCKET*)ClientSocket, (char*)&size, sizeof(size), 0 );
	iSendResult=send( *(SOCKET*)ClientSocket, outData, size, 0 );

	if (iSendResult == SOCKET_ERROR) {
		DEBUG(INFO,"send failed with error: %d\n", WSAGetLastError());
		closesocket(*(SOCKET*)ClientSocket);
		WSACleanup();
	}

	DEBUG(INFO,"Bytes sent: %d\n", iSendResult);
	DEBUG(INFO,"Buffer content:");
	for (i=0;i<size;i++){
		debug1("%02X",outData[i]);
	}
	debug1("\n");
}

void mycloseSocket(void* Socket){
	int iResult = 0;
	iResult = shutdown(*(SOCKET*)Socket, SD_SEND);

	if (iResult == SOCKET_ERROR) {
		DEBUG(INFO,"shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(*(SOCKET*)Socket);
		WSACleanup();
	}

	// cleanup
	closesocket(*(SOCKET*) Socket);
	*(SOCKET*) Socket = INVALID_SOCKET;
	//WSACleanup();
}

/*
 * NWManager_Interface.h
 *
 *  Created on: 18 déc. 2017
 *      Author: HZGF0437
 */


/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#ifndef NWMANAGER_INCLUDE_NWMANAGER_INTERFACE_H_
#define NWMANAGER_INCLUDE_NWMANAGER_INTERFACE_H_

/**
 * Initializes ListenSocket with TCP/IP address & port
 * @return ListenSocket
 */
void* initialize();

/**
 * Listens to socket
 * @param LSocket
 * @return status code
 */
uint32_t ext_listen( void* LSocket);


/**
 * Receives a connection on the ListenSocket and sends back a ConnectionSocket from which the data can be retrieved
 * @param ListenSocket
 * @return ConnectionSocket
 */
void* get_connection(void* ListenSocket);

/**
 * Send data to the ClientSocket
 * @param ClientSocket
 * @param outData
 * @param size
 */
void ext_send(void* ClientSocket, char* outData, uint32_t size);

/**
 * Receive until the peer shuts down the connection
 * @param ClientSocket
 * @param data
 * @return
 */
uint32_t ext_receive(void* ClientSocket, char* data);

/**
 * Close the socket
 * @param Socket Socket to be closed
 */
void mycloseSocket(void* Socket);

#endif /* NWMANAGER_INCLUDE_NWMANAGER_INTERFACE_H_ */

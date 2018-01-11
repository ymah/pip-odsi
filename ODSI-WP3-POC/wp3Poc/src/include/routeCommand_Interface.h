/*
 * routeCommand_Interface.h
 *
 *  Created on: 20 nov. 2017
 *      Author: hzgf0437
 */

/*FreeRTOS include*/
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#ifndef ROUTECOMMAND_INTERFACE_H_
#define ROUTECOMMAND_INTERFACE_H_

int routeCommand(event_t ReceivedValue, QueueHandle_t xQueue_AM2CM, QueueHandle_t xQueue_AM2KM);

#endif /* ROUTECOMMAND_INTERFACE_H_ */

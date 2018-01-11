/*
 * routeCommandSimple.h
 *
 *  Created on: 20 nov. 2017
 *      Author: hzgf0437
 */

/*FreeRTOS include*/
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "stdint.h"

#ifndef ROUTECOMMANDSIMPLE_H_
#define ROUTECOMMANDSIMPLE_H_

uint32_t routeCommandSimple(event_t ReceivedValue, QueueHandle_t xQueue_AM2CM, QueueHandle_t xQueue_AM2KM);


#endif /* ROUTECOMMANDSIMPLE_H_ */

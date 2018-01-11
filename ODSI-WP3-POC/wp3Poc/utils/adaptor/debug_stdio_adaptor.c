/*
 * debug_stdio_adaptor.c
 *
 *  Created on: 30 nov. 2017
 *      Author: hzgf0437
 */

#include "debug.h"
#include <stdio.h>

void debug(const char*string){
	if(string != NULL){
		printf("%s", string);
		fflush( stdout );
	}
}

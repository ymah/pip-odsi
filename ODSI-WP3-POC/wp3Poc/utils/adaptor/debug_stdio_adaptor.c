/*
 * debug_stdio_adaptor.c
 *
 *  Created on: 30 nov. 2017
 *      Author: hzgf0437
 */

#include "debug.h"
#include <stdio.h>
#include <stdarg.h>

void debug(const char*string){
	if(string != NULL){
		printf("%s", string);
		fflush( stdout );
	}
}

void debug1(const char *format, ...){
   va_list arg;

   va_start (arg, format);
   vfprintf (stdout, format, arg);
   va_end (arg);
   fflush( stdout );
}

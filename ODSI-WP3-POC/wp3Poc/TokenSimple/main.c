/*
 * main.c
 *
 *  Created on: 28 nov. 2017
 *      Author: hzgf0437
 */


#include "validateTokenSimple.h"
#include <stdio.h>

void main(void){

	if (token_validate_simple("Friend", 17) == 1){
		printf("Correct\n");
		fflush( stdout );}
	else{
		printf("Incorrect\n");
		fflush( stdout );}

	if (token_validate_simple("Pirate", 17) == 0){
		printf("Correct\n");
		fflush( stdout );}
	else{
		printf("Incorrect\n");
		fflush( stdout );}
}

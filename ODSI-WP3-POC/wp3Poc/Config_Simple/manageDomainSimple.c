/*
 * ManageDomain.c
 *
 *  Created on: 20 nov. 2017
 *      Author: hzgf0437
 */

/*-----------------------------------------------------------*/

#include "debug.h"
#include "string.h"
#include "CommonStructure.h"
#include "ResponseCode.h"
#include "stdint.h"

/*-----------------------------------------------------------*/

//domain_t CurrentDomain = {DOM_ID_OWNER,NB_CHILD_DOM_DEFAULT};

uint32_t createDomain(){
	debug("Create Domain\n");
	return SUCCESS;
}


uint32_t readDomID(domain_t *dom, char* readData){
	debug("Read ID: ");
	debug(dom->DomId);
	debug("\n)");
	strcpy(readData, dom->DomId);
	return SUCCESS;
}


uint32_t updateDomID(domain_t *dom, char* domId){
	debug("Update Domain ID: Old");
	debug(dom->DomId);
	debug("\n)");

	strcpy(dom->DomId,domId);

	debug("Update Domain ID: New");
	debug(dom->DomId);
	debug("\n)");
	return SUCCESS;
}

/*int nbDomChild(domain_t dom){
	printf("Command is not supported");
	fflush( stdout );
	return UNKNOWN_COMMAND;
}*/

/*-----------------------------------------------------------*/

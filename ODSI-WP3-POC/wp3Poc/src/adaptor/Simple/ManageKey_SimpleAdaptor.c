/*
 * ManageKey_SimpleAdaptor.c
 *
 *  Created on: 24 nov. 2017
 *      Author: hzgf0437
 */


/*-----------------------------------------------------------*/

/* Standard includes. */
#include "manageKeySimple.h"
#include "CommonStructure.h"
#include "ManageKey_Interface.h"
#include "ResponseCode.h"
#include "MyAppConfig.h"
#include "string.h"
#include "debug.h"

/* Kernel includes. */

/*-----------------------------------------------------------*/

/**
 * Testing doxygen
 * @param com For read command, the data expected is written as "KEY_ID:KEY_VALUE"
 * @param l_key
 * @param readData
 * @return
 */
int ManageKey(command_t com, key_t** l_key, char* readData){

	char key_ID[KEYID_SIZE]={};
	char keyValue[KEY_SIZE]={};
	int result;

	int i;
	for(i=0;com.data[i] != ':';i++)
		key_ID[i]=com.data[i];

	strcpy(keyValue, com.data+i+1);


	switch(com.instruction){
	case ADD_KEY :
		debug("add Key\n");
		return addKey(l_key, key_ID, keyValue);
	case READ_KEY :
		debug("read Key\n");
		result=readKey(*l_key, key_ID, readData);
		return result;
	case UPDATE_KEY :
		debug("update Key, new value: ");
		debug(keyValue);
		debug("\n");
		result=updateKey(*l_key, key_ID, keyValue);
		return result;
		break;
	case DELETE_KEY :
		debug("delete Key\n");
		return deleteKey(l_key, key_ID);
	default:
		debug("command is not supported\n");
		return UNKNOWN_COMMAND;
		break;
	}
}

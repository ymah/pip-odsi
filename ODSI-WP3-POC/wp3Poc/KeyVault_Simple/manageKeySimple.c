/*
 * manageKeySimple.c
 *
 *  Created on: 24 nov. 2017
 *      Author: hzgf0437
 */


/*-----------------------------------------------------------*/

/* Standard includes. */
#include "manageKeySimple.h"
#include "MyAppConfig.h"
#include "CommonStructure.h"
#include "ResponseCode.h"
#include "string.h"
#include "debug.h"
#include <stdlib.h>
#include "stdint.h"

/* Kernel includes. */

/*-----------------------------------------------------------*/

key_t* createKey(char* keyID, char* keyValue){
	key_t* key;
	key= (key_t*) malloc(sizeof(key_t));
	strcpy(key->KeyID,keyID);
	key->next=NULL;
	strcpy(key->Key,keyValue);

	return key;
}

uint32_t addKey(key_t** l_key, char* keyID, char* keyValue){
	key_t* old_l_key;
	old_l_key=*l_key;
	*l_key=createKey(keyID, keyValue);
	(*l_key)->next=old_l_key;
	return SUCCESS;
}

uint32_t readKey(key_t* l_key, char* key_ID, char* keyValue){
	key_t* current_key=NULL;

	for(current_key = l_key; current_key != NULL; current_key=current_key->next){
		if (strcmp(current_key->KeyID, key_ID) == 0){
			strcpy(keyValue,current_key->Key);
			return SUCCESS;
		}
	}
	return KEY_NOT_FOUND;
}

uint32_t updateKey(key_t* l_key, char* key_ID, char* keyValue){
	key_t* current_key=NULL;

	for(current_key = l_key; current_key != NULL; current_key=current_key->next){
		if (strcmp(current_key->KeyID, key_ID) == 0){
			strcpy(current_key->Key, keyValue);
			return SUCCESS;
		}
	}

 return KEY_NOT_FOUND;
}

uint32_t deleteKey(key_t** l_key, char* key_ID){
	key_t* current_key=NULL;
	key_t** previous_key=NULL;

	for(current_key = *l_key, previous_key= l_key; current_key != NULL; previous_key=&(current_key->next), current_key=current_key->next){
		if (strcmp(current_key->KeyID, key_ID) == 0){
			*previous_key=current_key->next;
			free(current_key);
			return SUCCESS;
		}
		 return KEY_NOT_FOUND;
	}

 return KEY_NOT_FOUND;
}

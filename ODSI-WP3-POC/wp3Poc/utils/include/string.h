/*
 * string.h
 *
 *  Created on: 21 nov. 2017
 *      Author: hzgf0437
 */

#ifndef INCLUDE_UTILS_STRING_H_
#define INCLUDE_UTILS_STRING_H_

char *strcpy(char *dest, char *src);
int strcmp(char* str1, char* str2);
int strlen(char* str);
void reverse(char s[]);
char* itoa(int n, char s[], int base);
int myatoi(char *str);
char* mystrcat(char *dest, const char *src);

#endif /* INCLUDE_UTILS_STRING_H_ */

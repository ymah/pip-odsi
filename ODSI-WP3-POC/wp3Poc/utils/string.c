/*
 * string.c
 *
 *  Created on: 21 nov. 2017
 *      Author: hzgf0437
 */

#include "string.h"

/**
 * Compares 2 strings
 * @param dest
 * @param src
 * @return dest
 */
char *strcpy(char *dest, char *src){
	unsigned i;
	for (i=0; src[i] != '\0'; ++i){
		dest[i] = src[i];
	}
	dest[i]='\0';
	return dest;
}

/**
 * Comparison of 2 strings
 * @param str1
 * @param str2
 * @return Returns 0 if strings are equal. Returns 1 if strings are different.
 */
int strcmp(char* str1, char* str2){
	int i=0;
	while (str1[i] == str2[i]){
		if (str2[i] == '\0')
			return 0;
		i++;
	}
	return 1;
}

/**
 * strlen: measure ength of the string
 * @param str
 * @return length of the string
 */
int strlen(char* str){
	int i=0;
	while (str[i] != '\0')
		i++;
	return i;
}

/**
 * reverse:  reverse string s in place
 * @param s string
 */
void reverse(char s[])
{
	int i, j;
	char c;

	for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

/**
 * itoa:  convert n to characters in s
 * @param n number to be converted
 * @param s output string
 * @param base base for conversion
 * @result string
 */
char* itoa(int n, char s[], int base){
	int i, sign;

	if ((sign = n) < 0)  /* record sign */
		n = -n;          /* make n positive */
	i = 0;
	do {       /* generate digits in reverse order */
		if( base > 10 && ((n % base) > 10) )
			s[i++] = n%base -10 + 'A';
		else
			s[i++] = n % base + '0';   /* get next digit */
	} while ((n /= base) > 0);     /* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
	return s;
}

/**
 * myatoi: convert string str to int
 * @param str
 * @return converted int
 */
int myatoi(char *str)
{
    int res = 0; // Initialize result

    // Iterate through all characters of input string and
    // update result
    for (int i = 0; str[i] != '\0'; ++i)
        res = res*10 + str[i] - '0';

    // return result.
    return res;
}

/**
 * mystrcat: concatenate string dest and src in dest
 * @param dest
 * @param src
 * @return concatenated string
 */
char* mystrcat(char *dest, const char *src){
	int i,j;
	for (i = 0; dest[i] != '\0'; i++)
		;
	for (j = 0; src[j] != '\0'; j++)
		dest[i+j] = src[j];
	dest[i+j] = '\0';
	return dest;
}



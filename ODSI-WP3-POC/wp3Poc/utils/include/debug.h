/*
 * Debug.h
 *
 *  Created on: 30 nov. 2017
 *      Author: hzgf0437
 */

#ifndef UTILS_INCLUDE_DEBUG_H_
#define UTILS_INCLUDE_DEBUG_H_

#define CRITICAL 1 // Error output
#define INFO 2 // Information output
#define TRACE 3 //verbose output
#define DEBUG 4 // debugging

#ifndef LOGLEVEL
#define LOGLEVEL INFO
#endif

#define DEBUG(l,s) if (l<=LOGLEVEL){debug( "[" #l "] " __FILE__ " : " s );}

void debug(const char*string);

#endif /* UTILS_INCLUDE_DEBUG_H_ */

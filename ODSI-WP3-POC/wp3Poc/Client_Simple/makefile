#Client Simple Makefile
CC = gcc
AR = ar
CFLAGS = -std=c99 -Wall -g -Os

FREERTOS_INCLUDE = -I../FreeRTOS/include -I../FreeRTOS -I../FreeRTOS/portable/MSVC-MingW
FREERTOS_TRACE_INCLUDE = -I../FreeRTOSPlusTrace/include -I../FreeRTOSPlusTrace/
UTILS_INCLUDE = -I../utils/include -I../src/include

INCLUDE = -Iinclude 
OBJ = obj/routeCommandSimple.o

clean:
	rm obj/*

install : obj/libclient_simple.a
	mv obj/libclient_simple.a ../lib/libclient_simple.a

obj/libclient_simple.a: $(OBJ)
	$(AR) -cq obj/libclient_simple.a $(OBJ) 

obj/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE) $(FREERTOS_INCLUDE) $(FREERTOS_TRACE_INCLUDE) $(UTILS_INCLUDE)

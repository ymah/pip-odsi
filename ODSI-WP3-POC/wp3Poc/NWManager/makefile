#NW MAnager Makefile
CC = gcc
AR = ar
CFLAGS = -std=c99 -Wall -g 

FREERTOS_INCLUDE = -I../FreeRTOS/include -I../FreeRTOS -I../FreeRTOS/portable/MSVC-MingW
FREERTOS_TRACE_INCLUDE = -I../FreeRTOSPlusTrace/include -I../FreeRTOSPlusTrace/
UTILS_INCLUDE = -I../utils/include -I../src/include
#WIN_INCLUDE = -IC:/MinGW/lib/gcc/mingw32/6.3.0/include

INCLUDE = -Iinclude

OBJ = obj/manageNW.o obj/NWManager.o

clean:
	rm obj/*

install : obj/libmanageNW.a
	mv obj/libmanageNW.a ../lib/libmanageNW.a

obj/libmanageNW.a: $(OBJ)
	$(AR) -cq obj/libmanageNW.a $(OBJ) 

obj/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE) $(FREERTOS_INCLUDE) $(FREERTOS_TRACE_INCLUDE) $(UTILS_INCLUDE) #$(WIN_INCLUDE)

obj/manageNW.o: portable/NW_WIN32/manageNW_WIN32.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE) $(FREERTOS_INCLUDE) $(FREERTOS_TRACE_INCLUDE) $(UTILS_INCLUDE) #$(WIN_INCLUDE)

#obj/manageNW.o: portable/NW_Simple/manageNW_simple.c
#	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE) $(FREERTOS_INCLUDE) $(FREERTOS_TRACE_INCLUDE) $(UTILS_INCLUDE)

	
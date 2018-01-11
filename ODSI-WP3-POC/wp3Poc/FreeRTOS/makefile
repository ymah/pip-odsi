#FreeRTOSTrace Makefile
CC = gcc
AR = ar
CFLAGS = -std=c99 -Wall -g -Os

OBJ = obj/list.o obj/queue.o obj/tasks.o obj/timers.o obj/croutine.o obj/event_groups.o obj/heap_5.o obj/port.o
INCLUDE = -Iinclude -Iportable/MSVC-MingW -I.

FREERTOS_TRACE_INCLUDE = -I../FreeRTOSPlusTrace/include -I../FreeRTOSPlusTrace/

clean:
	rm -f obj/*

install : obj/libfreertos.a
	mv obj/libfreertos.a ../lib/libfreertos.a

obj/libfreertos.a: $(OBJ)
	$(AR) -cq $@ $(OBJ) 

obj/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE) $(FREERTOS_TRACE_INCLUDE)
	
obj/heap_5.o: portable/MemMang/heap_5.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE) $(FREERTOS_TRACE_INCLUDE)

obj/port.o: portable/MSVC-MingW/port.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE) $(FREERTOS_TRACE_INCLUDE)
	

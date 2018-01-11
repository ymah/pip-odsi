#FreeRTOS Makefile
CC = gcc
AR = ar
CFLAGS = -std=c99 -Wall -g -Os

FREERTOS_INCLUDE = -I../FreeRTOS/include -I../FreeRTOS -I../FreeRTOS/portable/MSVC-MingW
INCLUDE = -Iinclude -I.
OBJ = obj/trcBase.o obj/trcHardwarePort.o obj/trcKernel.o obj/trcKernelPort.o obj/trcUser.o

clean:
	rm -f obj/*

install : obj/libfreertos_trace.a
	mv obj/libfreertos_trace.a ../lib/libfreertos_trace.a

obj/libfreertos_trace.a: $(OBJ)
	$(AR) -cq $@ $(OBJ) 

obj/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(FREERTOS_INCLUDE) $(INCLUDE)
	
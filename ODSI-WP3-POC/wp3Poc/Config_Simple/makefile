#Config Simple Makefile
CC = gcc
AR = ar
CFLAGS = -std=c99 -Wall -g -Os

UTILS_INCLUDE = -I../utils/include -I../src/include

INCLUDE = -Iinclude
OBJ = obj/manageDomainSimple.o

clean:
	rm obj/*

install : obj/libconfig_simple.a
	mv obj/libconfig_simple.a ../lib/libconfig_simple.a

obj/libconfig_simple.a: $(OBJ)
	$(AR) -cq obj/libconfig_simple.a $(OBJ) 

obj/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE) $(UTILS_INCLUDE)

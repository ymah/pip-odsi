#Key Vault Simple Makefile
CC = gcc
AR = ar
CFLAGS = -std=c99 -Wall -g -Os

UTILS_INCLUDE = -I../utils/include -I../src/include

INCLUDE = -Iinclude
OBJ = obj/manageKeySimple.o

clean:
	rm obj/*

install : obj/libkey_simple.a
	mv obj/libkey_simple.a ../lib/libkey_simple.a

obj/libkey_simple.a: $(OBJ)
	$(AR) -cq obj/libkey_simple.a $(OBJ) 

obj/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE) $(UTILS_INCLUDE)

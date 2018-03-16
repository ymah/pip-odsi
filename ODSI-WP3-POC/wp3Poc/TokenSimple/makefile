#Token Makefile
CC = gcc
AR = ar
CFLAGS = -std=c99 -Wall -g -Os

INCLUDE = -Iinclude
OBJ = obj/validateTokenSimple.o

clean:
	rm obj/*

install : obj/libtoken_simple.a 
	mv obj/libtoken_simple.a ../lib/libtoken_simple.a

obj/libtoken_simple.a: $(OBJ)
	$(AR) -cq $@ $(OBJ) 

obj/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)
	

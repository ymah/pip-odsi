#Utils Makefile
CC = gcc
AR = ar
CFLAGS = -std=c99 -Wall -g

INCLUDE = -Iinclude -I../src/include
OBJ = obj/string.o obj/debug_stdio_adaptor.o obj/structcopy.o obj/parser.o obj/mystdlib.o

clean:
	rm -f obj/*

install : obj/libutils.a
	mv obj/libutils.a ../lib/libutils.a

obj/libutils.a: $(OBJ)
	$(AR) -cq obj/libutils.a $(OBJ)

obj/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

obj/%.o: adaptor/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

CC = gcc
CFLAGS = -g -Wall -std=c99 -D_GNU_SOURCE
LDLIBS = -lm

all: cross connect

connect: board.o connect.o
	gcc board.o connect.o -o connect

connect.o: connect.c board.h
	gcc -Wall -std=c99 -c connect.c board.h

board.o: board.c board.h
	gcc -Wall -std=c99 -c board.c	board.h

cross: cross.o
	gcc cross.o -o cross

cross.o: cross.c
	gcc -Wall -std=c99 -c cross.c

clean:
	rm -f cross cross.o
	rm -f connect connect.o
	rm -f board.o
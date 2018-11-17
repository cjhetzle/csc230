# A makefile with explicit rules for everything we need to build.

# Compiler for the default rule to use.
CC = gcc

# extra options we want the default compile rule to use.
CFLAGS = -Wall -g -std=c99 -D_GNU_SOURCE
LDLIBS = -lm

all: squeeze unsqueeze dumpbits
squeeze: squeeze.o bits.o codes.o
unsqueeze: unsqueeze.o bits.o codes.o
dumpbits: dumpbits.o

bits.o: bits.h
codes.o: codes.h


clean:
	rm -f squeeze squeeze.o
	rm -f unsqueeze unsqueeze.o
	rm -f codes.o bits.o
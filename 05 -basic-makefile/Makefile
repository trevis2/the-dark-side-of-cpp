# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects

.PHONY = all clean

CC = g++                        # compiler to use

LINKERFLAG = -lm

SRCS := main.cpp
BINS := foo

all: main

main: main.o
	        @echo "Checking.."
	        ${CC} -lm main.o -o main

main.o: main.cpp
	        @echo "Creating object.."
	        ${CC} -c main.cpp

clean:
	        @echo "Cleaning up..."
	        rm -rvf f main.o main

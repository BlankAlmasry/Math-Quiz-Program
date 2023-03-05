CC=gcc
CFLAGS=-I.
.PHONY: all main run clean

all: main run clean

main: main.o
	@$(CC) -o main main.o

main.o: main.c
	@$(CC) -c -o main.o main.c $(CFLAGS)

run:
	@make main && ./main

clean:
	@rm -f *.o main

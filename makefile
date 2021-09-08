CC = gcc
CFLAGS = -Wall -Werror

all: driver

drive: main.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c log.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f driver main.o

CC = gcc
AR = ar
CFLAGS = -std=gnu11 -Wall -Wextra -Wpedantic -O2

.PHONY: all clean
all: arithmetic

arithmetic: main.o libfunctions.a
	$(CC) $(CFLAGS) main.o libfunctions.a -o $@

libfunctions.a: functions.o
	$(AR) rcs $@ $<

main.o: main.c headers.h
	$(CC) $(CFLAGS) -c main.c -o $@

functions.o: functions.c headers.h
	$(CC) $(CFLAGS) -c functions.c -o $@

clean:
	rm -f main.o functions.o libfunctions.a arithmetic

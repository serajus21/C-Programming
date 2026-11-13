CC = gcc
AR = ar
CFLAGS = -std=gnu11 -Wall -Wextra -Wpedantic -O0

.PHONY: all clean
all: arithmetic

arithmetic: main.o libfunctions.a memory_map.o
	$(CC) $(CFLAGS) main.o libfunctions.a memory_map.o -o $@

libfunctions.a: functions.o
	$(AR) rcs $@ $<

main.o: main.c headers.h memory_map.h
	$(CC) $(CFLAGS) -c main.c -o $@

functions.o: functions.c headers.h memory_map.h
	$(CC) $(CFLAGS) -c functions.c -o $@

memory_map.o: memory_map.c memory_map.h headers.h
	$(CC) $(CFLAGS) -c memory_map.c -o $@

clean:
	rm -f main.o functions.o memory_map.o libfunctions.a arithmetic

# Variables
CC = gcc
CFLAGS = -Wall -Wextra -c
AR = ar
ARFLAGS = -rcs
TARGET = avr-main-EXECUTABLE

# Object files and Libraries
OBJS = avr-main.o avr-source.o avr-lib.o
LIBS = libavr-source.a libavr-lib.a

# Default target: build the executable
all: $(TARGET)

# Link the executable using the compiled object and static libraries
$(TARGET): avr-main.o libavr-source.a libavr-lib.a
	$(CC) avr-main.o -L. -lavr-source -lavr-lib -o $(TARGET)

# Compile C source files into Object files
avr-main.o: avr-main.c
	$(CC) $(CFLAGS) avr-main.c -o avr-main.o

avr-source.o: avr-source.c
	$(CC) $(CFLAGS) avr-source.c -o avr-source.o

avr-lib.o: avr-lib.c
	$(CC) $(CFLAGS) avr-lib.c -o avr-lib.o

# Create static libraries from object files
libavr-source.a: avr-source.o
	$(AR) $(ARFLAGS) libavr-source.a avr-source.o

libavr-lib.a: avr-lib.o
	$(AR) $(ARFLAGS) libavr-lib.a avr-lib.o

# Clean up built binaries, objects, and archive libraries
clean:
	rm -f $(TARGET) $(OBJS) $(LIBS)

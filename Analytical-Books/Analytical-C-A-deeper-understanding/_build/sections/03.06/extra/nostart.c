// nostart.c
// A program that brings its own entry point instead of crt1.o's.
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    puts("hello, world");
    return 0;
}

void _start(void) {         // the linker's default entry point
    exit(main());           // no __libc_start_main, no argc, no argv
}

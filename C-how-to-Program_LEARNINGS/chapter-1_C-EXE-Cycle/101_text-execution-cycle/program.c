//program.c
//to demonstrate the text execution cycle in C
#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}

/*
    1. Preprocessing: gcc -E program.c -o program.i [-E flag means expand the source code to preprocessed output]
    2. Compilation: gcc -S program.i -o program.s [-S flag means compile the preprocessed output to assembly source code]
    3. Assembly: gcc -c program.s -o program.o [-c flag means assemble the assembly source code to object code]
    4. Linking: gcc program.o -o program [-o flag means link the object code to create an executable file]
*/
// arithmetic.c

#include <stdio.h>
#include <stdlib.h>

int *pointer = 0;

int main(void)
{

    /* pointer arithmetic init
    int a = 10;
    pointer = &a;

    puts("...Init...");
    printf("a = %d\n", a);
    printf("*pointer = %d\n", *pointer);
    puts("a = *pointer");

    puts("--------------Pointer Arithmetic--------------");
    printf("pointer (address of &a) = %p\n", pointer);
    printf("Size of a: %zu\n", sizeof(a));
    printf("Size of *pointer: %zu\n", sizeof(*pointer));
    printf("Size of pointer: %zu\n", sizeof(pointer));
    printf("pointer+1 = %p\n", pointer+1);
    */

    /*accessing array elements using pointer arithmetic | without index number*/
    int number[3] = {10,20,30};
    pointer = &number[0];

    printf("number[0]: %d\n", *pointer); // pointer = memory location | *pointer = object at that location
    printf("number[1]: %d\n", *(pointer+1)); // pointer+1 | *(pointer+1) = object after int's 4 byte location, another int 4 byte
    printf("number[2]: %d\n", *(pointer+2)); // pointer+2 | *(pointer+2) = ... go ... on .. + size 4 of int
    return 0;
}
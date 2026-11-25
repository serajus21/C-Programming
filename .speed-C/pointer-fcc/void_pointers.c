// void_pointers.c

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int x = 1025;         // x holding an int value
    void *pointer = 0;    // pointer defined, it occupies space in memory | it has no type | but still it can point (store memory location)
    int *intPointer = 0;  // intPointer defined, it occupies space in memory | it has int type
    intPointer = &x;      // x's memory location is stored in intPointer;
    pointer = intPointer; // though pointer has no type, it can hold memory_location of 4 bytes | now pointer and intPointer, both are pointing to x;

    printf("Memory Location of pointer: %p | %d\n", &pointer, &pointer);
    printf("Size of pointer: %zu\n", sizeof(pointer)); // 8 bytes

    printf("Memory Location of intPointer: %p | %d\n", &intPointer, &intPointer);
    printf("Size of pointer: %zu\n", sizeof(intPointer)); // 8 bytes

    // cross-checking
    printf("intPointer pointing to %p\n", pointer);
    printf("pointer pointing to: %p\n", intPointer);

    //value printing
    printf("pointer\'s pointing memory object: %d\n", *(int*)pointer);
    printf("intPointer\'s pointing memory object: %d\n", *intPointer);

    return 0;
}
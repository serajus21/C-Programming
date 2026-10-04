// pracs.c

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /*var pointer*/
    /*
    int *pointer = 0;  // defining pointer variable
    int number = 89;   // defining variable
    pointer = &number; // pointing to 'number' from 'pointer'
                       // 'pointer' holds the memory_addr of number, *pointer holds the object inside the pointer;

    printf("address of number | pointer: %d\n", pointer);         // address of number
    printf("address of number | &number: %d\n", &number);         // address of number
    printf("address of number | &(*pointer): %d\n", &(*pointer)); // address of number
    printf("address of pointer | &pointer: %d\n", &pointer);      // address of pointer
    printf("value of number | *pointer: %d\n", *pointer);         // dereferencing

    // Dereferencing
    *pointer = 45; // assign 45 to number; the location 'pointer' is pointing at;
                   // no new memory allocation for 45; it just replaces number's 89;
                   // so no memory location change | same location, but defferent value

    printf("address of number | pointer: %d\n", pointer);         // address of number
    printf("address of number | &number: %d\n", &number);         // address of number
    printf("address of number | &(*pointer): %d\n", &(*pointer)); // address of number
    printf("address of pointer | &pointer: %d\n", &pointer);      // address of pointer
    printf("value of number | *pointer: %d\n", *pointer);         // dereferencing
    */

    /*array pointer*/
    /*
    int *arrayPointer = 0;
    int myArray[4] = {10, 20, 30, 40};
    int arrayLength = sizeof(myArray) / sizeof(myArray[0]);
    arrayPointer = &myArray[0];

    for (int index = 0; index < arrayLength; index++)
    {
        printf("Value of myArray[%d] = %d | *(arrayPointer+%d) | addr_%p\n",
               index,
               *(arrayPointer + index), // int pointer array; fetches int from every 4 bytes; cause sizeof(int)=4;
               index,
               (arrayPointer + index)); // addresses are adjacent; so for int, pointer+1 steps ahead +4; cause sizeof(int)=4;
    }
    */

    /*casting pointer to another type*/
    /*
    int *numPointer = 0;
    int number = 1025;
    numPointer = &number;

    printf("Address of number | &number: %p\n", &number);
    printf("Address of number | numPointer: %p\n", numPointer);
    printf("Value of number | number %d\n", number);
    printf("Value of number | *numPointer: %d\n", *numPointer);

    char *charPointer = (char *)numPointer; // from now on, numPointer will point to same memory location
                                            // but it will fetch data from memory as if it's char; 1 byte each; casue sizeof(char)=1
                                            // pointer is still same with defferent fetching method, instead of int_4_bytes, fetches char_1_byte
                                            // pointing to same memory_location

    printf("Address of number_1stByte | &number: %p\n", &number);         // pointing to same memory like numPointer, equivalent to charPointer;
    printf("Address of number_1stByte | charPointer: %p\n", charPointer); // pointing to same memory like numPointer;
    printf("Value of number | number %d\n", number);                      // wil fetch all 4 bytes
    printf("Value of number_1stByte | *charPointer: %d\n", *charPointer); // will fetch only 1(1st) byte | 00000000 00000000 00000100 00000001 | 1 will be answer

    printf("Address of number_2ndByte | charPointer+1: %p\n", (charPointer + 1));  // unlike int's 4 byte, this address will be increased by 1 byte; cause sizeof(char) = 1;
    printf("Value of number_2ndByte | *(charPonter+1): %d\n", *(charPointer + 1)); // will fetch only 1(2nd) byte | 00000000 00000000 00000100 00000001 | 4 will be answer

    */

    return 0;
}
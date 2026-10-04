// init.c

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int value = 5;
    int *pointer = &value; // points to value's address
                           // int *pointer;
                           // pointer = &value;

    printf("value: %d\n", value);
    printf("pointer | address of value = %p\n", pointer);
    printf("&value = %p\n", &value);
    printf("*pointer | Value of \'value\': %d\n", *pointer);

    puts("-----------DEREFERENCING-------------");
    *pointer = 3;
    printf("value: %d\n", value);
    printf("pointer | address of value = %p\n", pointer);
    printf("&value = %p\n", &value);
    printf("*pointer | Value of \'value\': %d\n", *pointer);

    puts("---------UPDATING--------------");
    int value_2 = 21;
    pointer = &value_2;  // the location *pointer is holding, grab it's value, change it to value_2;
                         // "*pointer = value_2;" this doesn't point to value_2's memory location yet, until "pointer = &value_2;"
                         // we already declared *pointer before
    printf("value_2: %d\n", value_2);
    printf("pointer | address of value_2 = %p\n", pointer);
    printf("&value_2 = %p\n", &value_2);
    printf("*pointer | Value of \'value_2\': %d\n", *pointer);

    return 0;
}
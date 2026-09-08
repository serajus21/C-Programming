#include <stdio.h>
#include <string.h>
#define _divider "-----------------------------------------------\n"

int main(void)
{

    /* init
    int x = 3;
    printf("Address: %d | Value: %d\n", &x, *(&x));
    // printf("Address of operator: %d\n", &x);
    */

    /*printing values and address*/
    int x = 3;         // holds 3
    int *pointer = &x; // holds value of x, 3

    printf("Value of pointer %d\n", pointer);   // holds memory value only
    printf("Value of *pointer %d\n", *pointer); // holds value
    printf("Value of x: %d\n", x);
    printf("Value of &x: %d\n", &x);
    printf("Value of *(&x): %d\n", *(&x));
    printf("Value of &(pointer): %d\n", &(pointer));

    printf(_divider);
}

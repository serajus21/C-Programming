// array-maths.c
#include <stdio.h>

int main(void)
{
    // static
    /*
    int id[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int arrayLength = sizeof(id) / sizeof(id[0]);
    int total = 0;

    for(int i=0; i<arrayLength; i++) {
        total += id[i];
    }

    printf("SUM : %d\n", total);
    */

    /* definite - dynamic
    int array[5] = {0};
    int arrayLength = sizeof(array) / sizeof(array[0]);
    int total = 0;

    for (int i = 0; i < arrayLength; i++)
    {
        printf("Enter Value: ");
        scanf("%d", &array[i]);
        total += array[i];
    }

    printf("Array 0: %d\n", array[0]);
    printf("Total: %d\n", total);
    */

    /* INCOMPLETE !!! indefinite - dynamic | Sentinel value based input termination
    int number[] = {0};                                   // init array
    int arrayLength = sizeof(number) / sizeof(number[0]); // length
    int total = 0;                                        // init total
    int sentinel = -1;                                    // sentinel
    int number[0] = 0;                                    // init userInput variable
    printf("Enter Value: ");                              // prompt
    scanf("%d", &number[0]);                              // storing to memory

    */

    // Average
    int array[5] = {0};
    int arrayLength = sizeof(array) / sizeof(array[0]);
    int total = 0;

    for (int i = 0; i < arrayLength; i++)
    {
        printf("Enter %d/%d: ", i+1, arrayLength);
        scanf("%d", &array[i]);
        total += array[i];
    }

    double average = (double) total / arrayLength;
    printf("Aeverage: %.2f\n", average);
}

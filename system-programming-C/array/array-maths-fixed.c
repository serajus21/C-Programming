// array-maths-fixed.c
#include <stdio.h>

int main(void)
{
    // definite - dynamic
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

    return 0;
}

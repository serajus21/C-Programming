// array_as_funcArg.c

#include <stdio.h>
#include <stdlib.h>

/* passing array with it's size */
/*
int sumOfElements(int A[], int size)
{
    int sum = 0;
    for (int index = 0; index < size; index++)
    {
        sum += A[index];
    }
    return sum;
}

int main(void)
{
    int A[] = {1, 2, 3, 4, 5};
    int size_of_each = sizeof(A) / sizeof(A[0]);
    int total = sumOfElements(A, size_of_each);

    printf("Sum of elements: %d\n", total);

    return 0;
}
*/

/*passing array without it's size */
/*
int sumOfElements(int A[]) // actually it's (int* A); pointer to integer
                           // it first allocates a space in memory(stack) for itself, A to hold one elements at a time from main's A[] array
                           // assume it's recieves &A[0] from main; *A goes to that address and extract 4 bytes of value;
                           // then it extracts rest of the elements through pointer arithmetic and process goes on till end
                           // thus entire main's A[] doesn't get copied to call stack from main stack which is memory saver
{
    int sum = 0;
    int size = 0;
    size = sizeof(A) / sizeof(A[0]); // this can't work, cause arrays are passed as pointer-to-integer; so full size can't be known
                                     // main's A[] array, sends first &A[0], then &A[2] and so on untill ends;
                                     // that's why all the warnings are in terminal
    printf("A = %d | A[0] = %d\n", sizeof(A), sizeof(A[0]));
    printf("%d\n", sizeof(A));
    for (int index = 0; index < size; index++)
    {
        sum += A[index];
    }
    return sum;
}

int main(void)
{
    int A[] = {1, 2, 3, 4, 5};
    // int size_of_each = sizeof(A) / sizeof(A[0]);
    int total = sumOfElements(A);

    printf("Sum of elements: %d\n", total);
    printf("A = %d | A[0] = %d\n", sizeof(A), sizeof(A[0]));
    return 0;
}
*/

/* void function to get more clearer */
/*
void doubleArray(int *A, int size) // pointer to integer, equiv to A[]; receives only &A[0];
                                   // recieves the pointer-to-array's first element
{
    for (int mainArrayIndex = 0; mainArrayIndex < size; mainArrayIndex++)
    {
        A[mainArrayIndex] = 2 * A[mainArrayIndex]; // A only stores address of &A[0] | &A[0][mainArrayIndex] point to memory => *(&A[0])[mainArrayIndex] change inside memory
                                                   // goes to A[0]'s address, deref it to double
                                                   // then performs pointer arithmetic to jump 4 bytes [cause int] to fetch data
                                                   // then deref every four byte data to double
    }
}

int main(void)
{
    int A[5] = {1, 2, 3, 4, 5};                 // main's array
    int arrayLength = sizeof(A) / sizeof(A[0]); // size calculation
    doubleArray(A, arrayLength);                // A = arrayDecay | equiv to &A[0], sends a copy of address to doubleArray
                                                // by now doubleArray() reaches to every element's address of A[5], doubled them all

    for (int index = 0; index < arrayLength; index++) // as result this loop prints all elements of A[5], as doubled
    {
        printf("%d\t", A[index]);
    }
    puts("");
    return 0;
}
*/

/*passing-array to int_function | sum of elements*/
/*
int sumOfElements(int *addressFirstElement, int size)
{
    int total = 0;
    for (int mainArrayIndex = 0; mainArrayIndex < size; mainArrayIndex++)
    {
        total += *(addressFirstElement + mainArrayIndex); // total += A[index]
                                                          // as, *(addressFirstElement) = A[0]
                                                          // *(addressFirstElement + 1) = A[1]; pointer arithmetic
                                                          // list goes on...
    }
    return total;
}

int main(void)
{
    int A[5] = {1,2,3,4,5};
    int arrayLength = sizeof(A) / sizeof(A[0]);
    int total = sumOfElements(A, arrayLength);
    printf("Total = %d\n", total);
}
*/

/*passing-array to void_function*/
/*
void doubleArray(int *A, int size) // get the address of array's first elements
{
    for (int mainArIndex = 0; mainArIndex < size; mainArIndex++)
    {
        *(A + mainArIndex) = *(A + mainArIndex) * 2; // *(A + mainArIndex) => go to the address (A+mainArIndex) contains and hold it's value;
                                                     // *(A + mainArIndex) => it's the same value as array[index] from main;
                                                     // if (A + mainArIndex) is &array[index]; then, *(A + mainArIndex) is also equivalent to array[index]
                                                     // *(A + mainArIndex) * 2; this derefs array[index]'s value, make it double
    }
}

int main(void)
{
    int array[5] = {1, 2, 3, 4, 5};
    int arLength = sizeof(array) / sizeof(array[0]);
    doubleArray(array, arLength); // sends size and arLength;
    for (int index = 0; index < arLength; index++)
    {
        printf("%d\t", array[index]);
    }
    puts("");
}
*/
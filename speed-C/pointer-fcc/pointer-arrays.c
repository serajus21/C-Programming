// pointer-arrays.c

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int scores[5] = {234, 23425, 4, 534, 56};
    int *pointer = scores; // as scores is a array, & sign not needed | equivalent to '*pointer = score;'
                           // the array name is stored as first element's first bit address
                           // cause, array stores elements consecutively

    printf("Address of \'scores\'s first elements\'s first bit: %p | %p (verification)\n", &scores[0], pointer);
    printf("%d\n\n", scores);

    // printing arrayElements using pointer-to-int-array
    printf("%-15s%-15s%-15s%-15s\n", "Array", "Value", "Address(10)", "Address(%p)");
    printf("%-15s%-15s%-15s%-15s\n", "-----", "-----", "-----------", "-----------");
    for (int indexScore = 0; indexScore < (sizeof(scores) / sizeof(scores[0])); indexScore++)
    {
        printf("%-15d%-15d%-15d%-15p\n", indexScore, *(pointer + indexScore), (pointer + indexScore), (pointer + indexScore)); // pointer = address of first score elements
        printf("%-15d%-15d%-15d%-15p\n", indexScore, *(scores + indexScore), (scores + indexScore), (scores + indexScore));    // scores means, &score[0]; so, pointer works just fine
                                                                                                                               // without even using 'pointer' variable

        // printf("%-15d%-15d%-15d%-15p\n", indexScore, *(&scores[indexScore] + indexScore), (&scores[indexScore] + indexScore), (&scores[indexScore] + indexScore)); // &score[0] = pointer
        // so, works just fine
    }

    return 0;
}
// rSum.c
// calculate sum of a specific range provided by user

#define version "1.0"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int total = 0;                                     // global access variable
int rangeSum(int initValue, int terminationValue); // function prototype

int main(int eCount, char **data)
{
    // version
    if ((strcmp(data[1], "--version") == 0) || (strcmp(data[1], "-v") == 0))
    {
        puts(version);
        return 0;
    }
    // help
    if ((strcmp(data[1], "--help") == 0) || (strcmp(data[1], "-h") == 0))
    {
        puts("This program calculates sum of specific range");
        puts("<program-name>\t<initial-range>\t<termination-range>");
        return 0;
    }
    // processing
    printf("%d\n", rangeSum(atoi(data[1]), atoi(data[2])));
}


//rangeSum function definition
int rangeSum(int initValue, int terminationValue)
{
    for (int init_operand = initValue; init_operand <= terminationValue; init_operand++)
    {
        total += init_operand;
    }
    return total;
}
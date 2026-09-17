// factorial.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define version "1.0\n"
int fact(int n);

int main(int entryCount, char **entryData)
{
    // version
    if ((strcmp(entryData[1], "--version") == 0) || strcmp(entryData[1], "-v") == 0)
    {
        printf(version);
        return 0; // program termination message;
    }

    // help
    if((strcmp(entryData[1], "--help") == 0) || strcmp(entryData[1], "-h") == 0) {
        puts("factorial <userData>");
        return 0;
    }

    // factorial calc and printing
    int factorialResult = fact(atoi(entryData[1]));
    printf("%d\n", factorialResult);
    return 0; //program termination message;
}

// factorial function
int fact(int n)
{
    if (n == 1)
    {
        return n;
    }
    return n * fact(n - 1);
}
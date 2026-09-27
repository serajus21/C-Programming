// sum-cmd.c
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(int entryCounter, char **entries)
{
    int sum = 0;

    for (int entriesIndex = 0; entriesIndex < entryCounter; entriesIndex++)
    {
        sum += atoi(entries[entriesIndex]);
    }

    printf("%d\n", sum);
}
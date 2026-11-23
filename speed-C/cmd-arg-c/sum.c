//sum.c

#include <stdio.h>
#include <stdlib.h>

int main(int totalEntry, char *entries[]) 
{
    int sum = 0;

    for(int init=1; init<totalEntry; init++)
    {
        sum += atoi(entries[init]);
    }

    for(int init=1; init<totalEntry; init++)
    {
        if(init == totalEntry-1)
        {
            printf("%d = ", atoi(entries[init]));
        }
        else
        {
            printf("%d + ", atoi(entries[init]));
        }
    }

    printf("%d\n", sum);
return 0;
}
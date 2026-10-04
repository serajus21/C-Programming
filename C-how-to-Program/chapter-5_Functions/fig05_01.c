// fig05_01.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int square(int number);

int main(void)
{
    for (int count = 1; count <= 10; count++)
    {
        printf("%d ", square(count));
    }
    puts("");
    return 0;
}

int square(int number)
{
    return number * number;
}
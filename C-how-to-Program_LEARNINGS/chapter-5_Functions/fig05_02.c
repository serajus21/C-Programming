// fig05_02.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int max(int n1, int n2, int n3);

int main(void)
{
    int in_1 = 0, in_2 = 0, in_3 = 0;
    printf("%s", "Enter Three Numbers: ");
    scanf("%d%d%d", &in_1, &in_2, &in_3);
    printf("Max number is: %d\n", max(in_1, in_2, in_3));
    return 0;
}

int max(int n1, int n2, int n3)
{
    int max = n1;

    if (n2 > max)
    {
        max = n2;
    }

    if (n3 > max)
    {
        max = n3;
    }

    return max;
}
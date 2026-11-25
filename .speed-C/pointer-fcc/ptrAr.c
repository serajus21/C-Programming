// ptrAr.c

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int a[] = {4, 7, 9, 12};

    int *p = &a[1];
    int *q = &a[3];

    printf("%td\n", q - p);
    printf("q = %p\n", q);
    printf("(p+2) = %p\n", p + 2);

    return 0;
}
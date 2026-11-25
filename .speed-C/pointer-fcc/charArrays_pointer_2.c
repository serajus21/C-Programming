// charArrays_pointer_2.c

#include <stdio.h>
#include <stdlib.h>

void print(char *C)
{
    while (*C != '\0')
    {
        printf("%c", *C);
        C++;
    }
    puts("");
}

int main(void)
{
    char c[20] = "Hello";
    print(c);
    return 0;
}
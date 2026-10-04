// pointerType.c

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int a = 1025;
    int* p = &a;
    printf("size of integer: %zu bytes\n", sizeof(int));
    printf("Address = %d, value = %d\n", p, *p);
    printf("Address = %d, value = %d\n", p+1, *(p+1));

    // character pointer | points to a memory where character is stored
    char *p_char = (char*)p; //typecasting
    printf("size of char: %zu bytes\n", sizeof(char));
    printf("Address = %d, value = %d\n", p_char, *p_char);
    printf("Address = %d, value = %d\n", p_char+1, *(p_char+1));
    
    // void pointer | can't be dereferenced
    void *pointer = p;
    printf("Address of \'pointer\': %d\n", pointer);

    return 0;
}
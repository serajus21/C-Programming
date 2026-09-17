//init.c

#include<stdio.h>
int main(void) {
    int age = 21;
    int *pAge = &age;

    printf("address of age: (hex) %p\n", &age);
    printf("value of pAge: %p\n", pAge);
    // printf("address of age: (dec) %d\n", &age);
    
    printf("value of age: %d\n", age);
    printf("Value of stored address: %d\n", *pAge);
}
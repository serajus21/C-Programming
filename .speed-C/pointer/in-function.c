// in-function.c
// using pointer actually where it should be used

#include<stdio.h>

// void printAge(int age) {
//     printf("You are %d years old\n", age);
// }

void printAge(int *pointer) { // this is to print the value of stored address
    printf("You are %d years old\n", *pointer);
}


int main(void) {
    int age = 211;
    int *pAge = NULL;
    pAge = &age;
    printAge(pAge);
}
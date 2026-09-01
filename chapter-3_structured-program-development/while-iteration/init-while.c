// init-while.c
// checking frst power of 3, greater than 100;
// checking frst power of 2, greater than or equal to 1024;

#include<stdio.h>

int main(void) {
    // int product = 3;
    // while (product <= 100)
    // {
    //     product *= 3;
    // }
    // printf("First power of 3 larger than 100 is: %d\n", product);
    
    int product = 2;
    while (product < 1024)
    {
        product *= 2;
    }
    printf("First power of 2 larger than 1024 is: %d\n", product);
}
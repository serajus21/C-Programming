//copy-array.c

#include<stdio.h>
#include<stdlib.h>

int main(void) {
    int init_array[5] = {10,20,30,40,50};
    int target_array[5] = {};

    printf("Init Array: ");
    for (int i = 0; i < 5; i++)
    {
        printf("%d\t", init_array[i]);
    }
    puts("");

    printf("Target Array: ");
    for (int i = 0; i < 5; i++)
    {
        target_array[i] = init_array[i];
    }

    for (int i = 0; i < 5; i++)
    {
        printf("%d\t", target_array[i]);
    }
    puts("");


    
}
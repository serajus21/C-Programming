//list.c

#include<stdio.h>

int main(void) {
    int num[5] = {0,1,2,3,4};
    char alp[5] = {'a','b','c','d', 'e'};

    // printf("%-20s %-20s\n", "Number", "Alphabets"); //left
    printf("%-6s %20s\n", "Number", "Alphabets"); //mixed | right-left

    for(int numIndex=0; numIndex<5; numIndex++) {
        // printf("%-20d %-20c\n", num[numIndex], alp[numIndex]); //left
        printf("%6d %20c\n", num[numIndex], alp[numIndex]); //right
    }
}
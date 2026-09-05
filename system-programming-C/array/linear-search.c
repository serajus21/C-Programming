//linear-search.c

#include<stdio.h>
int main(void) {
    //variables
    int numbers[5] = {3,4,2,6,9};
    int _arr_length = sizeof(numbers) / sizeof(numbers[0]);
    int searchNumber = 0;
    int found_indicator = 0;
    //userInput
    printf("Enter Number You are looking for: ");
    scanf("%d", &searchNumber);
    //linear-search
    for(int index=0; index<_arr_length; index++) {
        if(searchNumber == numbers[index]) {
            printf("FOUND | index %d | position %d\n: ", index, index+1);
            found_indicator = 1;
            break;
        }
    }
    //if not found
    if(found_indicator == 0) {
        printf("Could not find: %d\n", searchNumber);
    }
}
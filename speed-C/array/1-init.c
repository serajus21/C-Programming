// 1-init.c

#include <stdio.h>
#include <string.h>

int main(void)
{
    /* totalling array element [for loop]
    // variable
    int numbers[5] = {2, 1, 4, 1, 5};
    int total = 0;
    int _arr_length = sizeof(numbers) / sizeof(numbers[0]);
    // process
    for (int index = 0; index < _arr_length; index++)
    {
        total += numbers[index];
    }
    // printing
    printf("Total: %d\n", total);
    // printf("%d\n", sizeof(numbers) / sizeof(numbers[0])); // we've five 'four(s)', array-size = 5
    */

    /* wrong input methodology
    int numbers[5] = {};
    int _arr_size = sizeof(numbers) / sizeof(numbers[0]);
    int total = 0;

    for(int index=0; index<_arr_size; index++) {
        int number = 0;
        printf("Enter Number(%d | %d): ", numbers[index], _arr_size);
        scanf("%d", &number);
        total += number;
    }

    printf("Total: %d\n", total);
    */

    /* Static ! Receive inputs from user, store them in array, sum up array elements
    // variables
    int numbers[5] = {};
    int _arr_size = sizeof(numbers) / sizeof(numbers[0]);
    int total = 0;
    // userInputs for array
    for(int index=0; index<_arr_size; index++) {
        printf("Input numbers %d/%d: ", (index+1), _arr_size);
        scanf("%d", &numbers[index]);
    }
    //printing arrays | summing up array
    for(int index=0; index<_arr_size; index++) {
        printf("You Entered Number %d/%d: %d\n", index+1, _arr_size, numbers[index]);
        total += numbers[index];
    }
    //printing arrays
    printf("Total: %d\n", total);
    */

    /* Dynamic ! Receive inputs from user, store them in array, sum up array elements
    // variable
    int numbers[] = {};
    int _arr_size = sizeof(numbers) / sizeof(numbers[0]);
    int total = 0;
    //sentinel controlled iteration
    int senti............. [STUCK !!!!!!!!!!!!!!]
    while ()
    {
        
    }
    */
    
}
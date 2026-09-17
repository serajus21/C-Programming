// app.c : prgram of main() functions
/*
1. Ask user how many operads he has
2. Create Array of specifice size to store them
3. Ask user enter operands one by one
4. Process them and store result in a variable
    - Use while/for loop
    - use array length as limit
5. Print the result and terminate program
*/

#include<stdio.h>
// #include "header.h"
int _sum_processor(int _operand_counter, int _user_total_input, int _operand_value, int _total);

int main(void) {
    int userTotalInput = 0;
    int operandCounter = 1;
    int operandValue = 0;
    int total = 0;

    printf("Enter Total Operand: "); scanf("%d", &userTotalInput);

    _sum_processor(operandCounter,userTotalInput,operandValue,total);

    // while (operandCounter <= userTotalInput)
    // {
    //     int userOperandValue = 0;
    //     printf("Enter Operand _%d_: ", operandCounter);
    //     scanf("%d", &userOperandValue);
    //     total += userOperandValue;
    //     operandCounter++;
    // }

    printf("%-15s %-15s\n", "Operands", "Total");
    printf("%-15d %-15d\n", operandCounter-1, total);
    
}


int _sum_processor(int _operand_counter, int _user_total_input, int _operand_value, int _total)
{
    while (_operand_counter <= _user_total_input)
    {
        _operand_value = 0;
        printf("Enter Operand _%d_: ", _operand_counter);
        scanf("%d", &_operand_value);
        _total += _operand_value;
        _operand_counter++;
    }
}
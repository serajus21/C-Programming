// processor-sum.c
#include <stdio.h>

int _sum_processor(int _operand_counter, int _user_total_input, int _operand_value, int _total)
{
    while (_operand_counter <= _user_total_input)
    {
        _operand_value = 0;
        printf("Enter Operand _%d_: ", _operand_counter);
        scanf("%d", &_operand_value);
        _total += _operand_value;
    }
}
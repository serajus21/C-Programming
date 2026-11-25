// div-cmd.c

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(int operandCounter, char **operands) {
    // for(int operandsIndex = 0; operandsIndex < operandCounter; operandsIndex++) {
        
    // }

    if(operandCounter != 3) {
        puts("USAGE: ./div-cmd operand_1 operand_2 | operand_1 > operand_2");
        return 1;
    }

    int counter = 0;
    int op_1 = atoi(operands[1]);
    int op_2 = atoi(operands[2]);

    while (op_1 > 0)
    {
        op_1 -= op_2;
        counter++;
    }

    printf("%d\n", counter);
    
}
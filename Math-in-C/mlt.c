//mlt.c
#include<stdio.h>

int main(void) {
    int op1 = 3, op2 = 4;
    int op1Array[3] = {op1,op1,op1};
    int op1ArrLength = sizeof(op1Array) / sizeof(op1Array[0]);

    int result = 0;
    
    for(int op1ArIndex=0; op1ArIndex<op1ArrLength; op1ArIndex++) {
        result += op2;
    }

    printf("%d X %d = %d\n", op1,op2,result);
    return 0;
}
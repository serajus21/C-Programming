//_mlt.c
// program to calculate two flaot numbers

#include<stdio.h>
#include<stdlib.h>

int main(int operandCount, char **operands) {
    float timesToIncrease = atof(operands[1]);
    float toBeIncreased = atof(operands[2]);
    float counter = 0.0; 
    float result = 0;

    while (counter < timesToIncrease)
    {
        result += toBeIncreased;
        counter += timesToIncrease;
    }

    printf("%.2f\n", result);   
}
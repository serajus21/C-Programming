//recursion.c

#include<stdio.h>
long long int recursiveFact(long long int userInput);


int main(void) {
    long long int number = 0;
    printf("Enter a number of: ");
    scanf("%d", &number);

    printf("Factorail is: %d\n", recursiveFact(number));
}

long long int recursiveFact(long long int userInput) {
    if(userInput == 1) {
        return 1;
    }
    return userInput * recursiveFact(userInput - 1);
}
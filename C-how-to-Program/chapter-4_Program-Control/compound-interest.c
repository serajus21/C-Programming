//compound-interest.c

#include<stdio.h>
#include<math.h>

int main(void) {
    double principal = 1000.0; //starting principal
    double rate = 0.05; // annual interest rate

    //output table column heads
    printf("%4s%21s\n", "Year", "Amount on Deposite");

    //calculate amount on deposite for each 10 years
    for(int year=1; year<=10; ++year) {
        double amount = principal * pow(1.0 + rate, year); //calculate new amount for specified year
        printf("%4d%21.2f\n", year, amount); //output one table row
    }
}

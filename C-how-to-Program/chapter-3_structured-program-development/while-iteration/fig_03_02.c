// fig_03_02.c
/*
A class of ten students took a quiz. The grades (integers in the range 0 to 100)
for this quiz are available to you. Determine the class average on the quiz.

- set total to zero
- set counter to one

- while counter <= 10
- take grade input from user
- add grade to total
- inc counter by 1

- set average to total divided by 10 [definite iteration]
- print average

*/

#include<stdio.h>
int main(void) { //main starts here
    // init phase
    int total = 0; // set to total to zero
    int counter = 1; //numbe of the grades to be entered next

    // process phase
    while (counter<=10)
    {
        int grade = 0; // init grade to zero
        printf("%s", "Enter Grade: "); //User Prompt
        scanf("%d", &grade); //receiving grade
        total += grade; // storing grade to total
        counter++; //increasing counter by 1
    }

    int average = total / 10; // calculating average
    printf("Class Average is: %d\n", average); // printing average
}


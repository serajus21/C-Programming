// class-average_counter-controll.c
/*
A class of ten students took a quiz. The grades (integers in the range 0 to 100)
for this quiz are available to you. Determine the class average on the quiz.

pseudocode
set counter to 1
set grade to zero
-get the first grade

while counter is less than or equal to 10
grade += grade
get new grade
increase counter by 1

calculate average = grade/10
print average
*/

#include <stdio.h>
int main(void)
{
    int total = 0;
    int counter = 1;

    while (counter <= 10) // condition
    {
        int grade = 0;
        printf("Enter Grade | %d: ", counter);
        scanf("%d", &grade); // receiving grade
        total += grade;      // adding grade to total
        counter++;           // incrementing by 1 of counter
    }
    float average = total / (counter - 1);                           // as counter must be false to exit loop, reduce 1 to get average
    printf("Average of %d students is: %f\n", counter - 1, average); // printing average
}
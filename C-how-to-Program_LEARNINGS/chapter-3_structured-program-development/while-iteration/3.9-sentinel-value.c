/*
#File: 3.9-sentinel-value.c
#Problem: Develop a class-averaging program that will process an arbitrary number of grades each time the program is run.
#Psedocode: Determine the class average for the quiz
    - init variables
        - init total to zero
        - init counter to zero
    - input, sum and count quiz grades
        - input the first grade (possibly the sentinel)
        - while the input isn't sentinel
            # add grade to total
            # add 1 to grade counter
            # ask for another grade input (possibly the sentinel)
    - calc and print the class average
        - if the counter is not equal to zero
            # set average to total divided by counter
            # print average
         else
            # print "No grades were entered"
*/

#include <stdio.h>

int main(void)
{
    // ---------------- inititalization phase ----------------
    int total = 0;
    int counter = 0;

    //---------------- processing phase ----------------
    // recieving first grade
    int grade = 0;
    printf("%s", "Enter first grade, -1 to exit: "); // prompt
    scanf("%d", &grade);                             // storing grade to memory
    // condition checking and proceeding
    while (grade != -1)
    {
        total += grade;                                 // updating total
        counter += 1;                                   // updating counter
        grade = 0;                                      // resetting grade value
        printf("%s", "Enter next grade, -1 to exit: "); // prompt for grade
        scanf("%d", &grade);                            // storing grade to memory
    }

    //---------------- termination phase ----------------
    if (counter != 0)
    {                                                                  // avoiding crash (dividing by zero) possibilites of dividing by zero
        double average = (double) total / counter;                                 // calculating average
        printf("The average of %d students is: %.2f\n", counter, average); // printing average
    }
    else
    {
        printf("%s", "No grades entered\n"); // no grade message
    }
}
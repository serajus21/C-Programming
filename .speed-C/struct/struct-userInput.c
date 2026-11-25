// struct-userInput.c
#include <stdio.h>

struct studentData
{
    int age;
    char section;
    float score;
};

int main(void)
{
    struct studentData student[5];
    int studentLength = sizeof(student) / sizeof(student[0]);

    // printf("%d\n", studentLength);

    // recieving input
    for (int st_index = 0; st_index < studentLength; st_index++)
    {
        // age input
        printf("Enter St_%d age: ", st_index + 1);
        scanf("%d", &student[st_index].age);
        // section input
        printf("Enter St_%d section: ", st_index + 1);
        scanf(" %c", &student[st_index].section);
        // scor input
        printf("Enter St_%d Score: ", st_index + 1);
        scanf("%f", &student[st_index].score);
    }

    puts("Processing Your Input...\n");

    // output
    for (int st_index = 0; st_index < studentLength; st_index++)
    {
        printf("St_%d | Age: %d, Section: %c, Score: %.2f\n",
               st_index + 1, student[st_index].age, student[st_index].section, student[st_index].score);
    }

    // termination message
    puts("I/O Done | Program terminated");
}
// student-data.c
// receive student data and show them

#include <stdio.h>

struct students
{
    char name[25];
    int id;
};

int main(void)









{
    struct students st[2] = {};
    int stLength = sizeof(st) / sizeof(st[0]);
    // printf("%d\n",stLength); --- working fine

    for (int stIndex = 0; stIndex < stLength; stIndex++)
    {
        // receiving name
        printf("Enter Name of Student %d: ", stIndex + 1);
        scanf("%s", &st[stIndex].name);
        // receiving id
        printf("Enter id of student %d: ", stIndex + 1);
        scanf("%d", &st[stIndex].id);
    }

    // printf("\n%-25s%-15s\n", "Student Name", "Student ID");
    // printf("%-25s%-15s\n", "------------", "-----------");

    // for(int stIndex = 0; stIndex < stLength; stIndex++) {
    //     printf("%-25s%-15d\n", st[stIndex].name, st[stIndex].id);
    // }

    printf("\n%-15s%-15s\n", "Student Name", "Student ID");
    printf("%-15s%-15s\n", "------------", "-----------");

    for (int stIndex = 0; stIndex < stLength; stIndex++)
    {
        printf("%-15s%-15d\n", st[stIndex].name, st[stIndex].id);
    }
}
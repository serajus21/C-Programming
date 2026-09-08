// struct-shorthand.c
#include <stdio.h>

struct Students
{
    int id;
    char section;
    float score;
};

int main(void)
{
    struct Students st[3] = {
        {34, 'A', 43.22},
        {22, 'B', 54.25},
        {11, 'N', 90.67}};

    int stLength = sizeof(st) / sizeof(st[0]);

    for (int stIndex = 0; stIndex < stLength; stIndex++)
    {
        printf("STUDENT_%d | id: %d, section: %c, score: %.2f\n",
               stIndex + 1, st[stIndex].id, st[stIndex].section, st[stIndex].score);
    }
}
// userInput.c : Array only allows same data-type

#include <stdio.h>
int main(void)
{
    int studentCard[5][2] = {
        {6881, 90},
        {3432, 72},
        {2345, 98},
        {9303, 43},
        {7839, 76}
    };

    printf("%-15s %-10s\n", "Student ID", "Score");

    for (int ri = 0; ri < 5; ri++)
    {
        printf("%-15d %-10d\n", studentCard[ri][0], studentCard[ri][1]);
    }
}
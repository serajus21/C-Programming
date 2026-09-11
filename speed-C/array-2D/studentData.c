// studentData.c
// observe how it recieves data from multiple rows-cols

#include <stdio.h>

int main(void)
{
    int studentData[5][5] = {
        {222156458, 98, 53, 23, 87},
        {231847562, 76, 91, 45, 68},
        {219374851, 84, 62, 77, 95},
        {245612739, 55, 88, 34, 72},
        {208493617, 93, 47, 81, 59}};

    printf("%-15s%-8s%-8s%-8s%-8s\n", "Studen ID", "PROG", "EEE", "EMB", "ENG");

    for (int ri = 0; ri < 5; ri++)
    {
        for (int ci = 0; ci < 5; ci++)
        {
            if (ci == 0)
            {
                printf("%-15d", studentData[ri][ci]);
            }
            else
            {
                printf("%-8d", studentData[ri][ci]);
            }
        }
        puts("");
    }

    return 0;
}
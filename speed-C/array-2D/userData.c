// userData.c

#include <stdio.h>
int main(void)
{
    int char userData[2][2] = {
        {342, 'Serajus'}, // row-1 id-name
        {334, 'Salehin'}  // row-2 id-name
    };
    printf("ID: %d, Name: %s", userData[0][0], userData[0][1]); // 342 Serajus
}
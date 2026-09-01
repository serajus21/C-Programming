// #include<stdio.h>
// int main(void) {
//     int x,y;
//     scanf("%d %d", &x,&y);
//     printf("%d\n",x+y);
// }

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: sum <x> <y>\n");
        return 1;
    }

    int x = atoi(argv[1]);
    int y = atoi(argv[2]);

    printf("%d\n", x + y);

    return 0;
}
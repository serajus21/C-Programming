// linear-search-2.c

#include <stdio.h>

int main(void)
{
    int id[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int arrayLength = sizeof(id) / sizeof(id[0]);

    printf("Enter Your ID: ");
    int ind_id = 0;
    scanf("%d", &ind_id);
    int found_indicator = 0;

    for (int index = 0; index < arrayLength; index++)
    {
        if (ind_id == id[index])
        {
            printf("Found\n");
            found_indicator = 1;
            break;
        }
    }

    if(found_indicator == 0) {
        printf("Could Not Find\n");
    }
}
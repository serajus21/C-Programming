// writing to a file

#include <stdio.h>
#include <string.h>

int main(void)
{
    char userDetails[200] = "Serajus Salehin | 25 | Bangaldesh | C-Programmer";
    FILE *userDetailsFile = fopen("userDetails.txt", "w");

    /* write as string
    if (userDetailsFile == NULL)
    {
        puts("We could not write to your file");
    }
    else
    {
        fputs(userDetails, userDetailsFile);
        fclose(userDetailsFile);
        puts("Your file has written | STRING");
    }
    */

    /* write as character
    if (userDetailsFile == NULL)
    {
        puts("We could not write to your file");
    }
    else
    {
        for (int index = 0; index < strlen(userDetails); index++)
        {
            fputc(userDetails[index], userDetailsFile);
        }
        fclose(userDetailsFile);
        puts("Your file has written successfully | char by char");
    }
    */
}
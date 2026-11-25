// customTouch.c
/*
    - _touch [a custom version of GNOME touch]
    - creates new file of any extension
        - if argument is more than two, shows error message | Guide
        - if file already exists, shows error message
        - if user creates .c file, adds template to file
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int entriesCount, char *entries[]) // counter : counts total entry | entries[] : holds user inputs
{                                           // main starts with args[]

    // if user enters inappropriate counts of arguments, shows error message | Guide to usage
    if (entriesCount != 2)
    {
        puts("Usage: _touch <filename.extension>");
        puts("Only one file can be created at a time");
        return 1;
    }

    FILE *myFile = fopen(entries[1], "wx"); // entries[0] : command | entries[1] : fileName | "w-write x-exclusiveWrite"

    // if file already exists, shows error message
    if (myFile == NULL)
    {
        puts("File already exists");
        return 1;
    }

    // if user creates a .c file, file will be created along with template
    int char_lenght_of_fileName = strlen(entries[1]);
    if (char_lenght_of_fileName >= 2 && entries[1][char_lenght_of_fileName - 2] == '.' && entries[1][char_lenght_of_fileName - 1] == 'c')
    {
        fprintf(myFile,
                "//%s\n\n"                                     // name of file
                "#include <stdio.h> \n#include <stdlib.h>\n\n" // file header
                "int main(void) {\n\n\n"                       // main function starts
                "return 0;\n"                                  // return value
                "}",                                           // main function ends
                entries[1]);                                   // call to 'name of file'
    }

    fclose(myFile);
    return 0;
}
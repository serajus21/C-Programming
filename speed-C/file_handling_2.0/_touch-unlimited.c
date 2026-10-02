//_touch-unlimited.c

// customTouch.c
/*
    - _touch [a custom version of GNOME touch]
    - creates new file of any extension
        - enable flags for help and version
        - prevent users creating unintended files
        - user should create as many files they want
        - if file already exists, shows error message
        - if user creates .c file, adds template to file

        continue : iterration termination | break : loop termination | return : program termination
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define version "_touch 26.0.3"

int main(int count, char *entries[]) // counter : counts total entry | entries[] : holds user inputs
{                                    // main starts with args[]

    // creating unlimited files
    for (int index = 1; index < count; index++)
    {
        // -h | --help
        if (strcmp(entries[index], "-h") == 0 || strcmp(entries[index], "--help") == 0)
        {
            puts("usage : _touch <filename.ext> <filename.ext> .......... <filename.ext>");
            puts("You can create as much as files you want");
            puts("Attempting to create an existing file will result an error | Only new files will be created");
            return 0; // program terminates [main function terminates]
        }

        // -v | --version
        if (strcmp(entries[index], "-v") == 0 || strcmp(entries[index], "--version") == 0)
        {
            puts(version);
            return 0; // program terminates [main function terminates]
        }

        // prevent creating unintended files; i.e. without extension
        if (strchr(entries[index], '.') == NULL)
        {
            printf("%s | unintended file name\n", entries[index]);
            continue; // next iteration
        }

        // create all files if new
        FILE *file = fopen(entries[index], "wx"); // entries[0] : command | entries[index > 0] : file | "w-write x-exclusiveWrite"

        // if file already exists, shows error message | create other files except existing ones
        if (file == NULL)
        {
            printf("%s already exists\n", entries[index]);
            continue; // next iteration
        }

        // .c FILE | if user creates a .c file, file will be created along with template
        int fileName_lenght = strlen(entries[index]);
        if (fileName_lenght >= 2 && entries[index][fileName_lenght - 2] == '.' && entries[index][fileName_lenght - 1] == 'c')
        {
            fprintf(file,
                    "//%s\n\n"                                     // name of file
                    "#include <stdio.h> \n#include <stdlib.h>\n\n" // file header
                    "int main(void) {\n\n\n"                       // main function starts
                    "return 0;\n"                                  // return value
                    "}",                                           // main function ends
                    entries[index]);                               // call to 'name of file'
        }
        fclose(file);
    }

    return 0;
}
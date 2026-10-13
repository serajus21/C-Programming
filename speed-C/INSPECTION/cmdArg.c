// cmdArg.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int counts, char **fileNames)
{
    for (int fileNamesIndex = 0; fileNamesIndex < counts; fileNamesIndex++) // excluding program name ./program
    {
        // /* INSPECTION
        printf("FILE (*fileNames) : %s | ADD (fileNames) : %p\n", fileNames[fileNamesIndex], &fileNames[fileNamesIndex]); // printing file names
        int fileNameLength = strlen(fileNames[fileNamesIndex]);                                  // printing char-by-char
        for (int fileCharIndex = 0; fileCharIndex < fileNameLength; fileCharIndex++)
        {
            printf("%s => [%d(%p)][%d(%p)] <=> %c | %p\n",
                   fileNames[fileNamesIndex],
                   fileNamesIndex, &fileNamesIndex,
                   fileCharIndex, &fileCharIndex,
                   fileNames[fileNamesIndex][fileCharIndex],
                   &fileNames[fileNamesIndex][fileCharIndex]);
        }
        puts("");
        
        printf("%-20s %-20s %-20s %-20s\n", "VARIABLE", "ADDRESS", "VALUE(%d)", "VALUE(%p)");
        printf("%-20s %-20s %-20s %-20s\n", "--------------------", "--------------------", "--------------------", "--------------------");
        printf("%-20s %-20p %-20d %-20s\n", "counts", &counts, counts, "---");
        printf("%-20s %-20p %-20d %-20p\n", "fileNames", &(fileNames), fileNames, fileNames);
        printf("%-20s %-20p %-20d %-20p\n", "*fileNames", &(*fileNames), *fileNames, *fileNames);
        printf("%-20s %-20p %-20d %-20p\n", "**fileNames", &(**fileNames), **fileNames, **fileNames);

        puts("");
        // */

        /*
        // all flags '-' '--'
        if ((strcmp(fileNames[fileNamesIndex], "-h") == 0) || (strcmp(fileNames[fileNamesIndex], "--help") == 0)) // help module
        {
            puts("Help Module");
            break; // terminates loop
        }
        if ((strcmp(fileNames[fileNamesIndex], "-v") == 0) || (strcmp(fileNames[fileNamesIndex], "--version") == 0)) // version module
        {
            puts("Version Module");
            break; // terminates loop
        }

        if (strchr(fileNames[fileNamesIndex], '.') == NULL) // preventing unintended file without extension
        {
            printf("%s | Uninted File Creation, extension required\n", fileNames[fileNamesIndex]);
            continue; // terminates iteration; directs to next iteration
        }

        // fileCreation
        FILE *file = fopen(fileNames[fileNamesIndex], "wx");

        if (file == NULL) // repeation prevention
        {
            printf("%s already exists\n", fileNames[fileNamesIndex]);
            continue; // terminates iteration; directs to next iteration
        } else { // file succession message
            printf("%s Created Successfully\n", fileNames[fileNamesIndex]);
            // continue; // terminates iteration; directs to next iteration | PROGRAM FORWARD TO NEXT STATEMENT
        }

        // template creation for specific language
        int fileNameLength = strlen(fileNames[fileNamesIndex]);
        // for .c
        if (fileNameLength > 2 && fileNames[fileNamesIndex][fileNameLength - 2] == '.' && fileNames[fileNamesIndex][fileNameLength - 1] == 'c')
        {
            fprintf(file,
                    "// %s\n"
                    "#include<stdio.h>\n"
                    "#include<stdlib.h>\n"
                    "#include<string.h>\n"
                    "#include<time.h>\n"
                    "#include<math.h>\n\n"
                    "int main(void)\n{\n\nreturn 0;\n}",
                    fileNames[fileNamesIndex]);
        }
        */
    }
    return 0; // terminates main()
}
// main-argument.c

/* init of cmd arguemnt | Print only
#include <stdio.h>
int main(int argc, char **argv)
{
    // argc => argument count (includes program name)
    // argv => argument vector
    printf("Total Argument Entered | argc => %d\n", argc);

    for (int argvIndex = 0; argvIndex < argc; argvIndex++)
    {
        printf("argvIndex %d | %s\n", argvIndex, argv[argvIndex]);
    }
}
*/

/* printing arguments without file name
#include<stdio.h>
int main(int argCount, int **argData_toBePrinted) {
    for(int argData_index = 0; argData_index < argCount; argData_index++) {
        if(argData_index > 0) { // this condition prevents printing prgram name itself
            printf("%s\n", argData_toBePrinted[argData_index]);
        }
    }
}
*/

/* sum | indefinite entries | atoi 'ascii to integer'
#include <stdio.h>
#include <stdlib.h>
int main(int numberCounter, char **numberEntries)
{
    int sum = 0;
    for (int entriesIndex = 1; entriesIndex < numberCounter; entriesIndex++) {
        sum += atoi(numberEntries[entriesIndex]);
    }
    printf("%d\n", sum);
}
*/

// /* sum } atof 'ascii to float'
#include <stdio.h>
#include <stdlib.h>
int main(int entriesCounter, char **entriesData) {
    float sum = 0.0;
    for(int entriesIndex = 1; entriesIndex < entriesCounter ; entriesIndex++) {
        sum += atof(entriesData[entriesIndex]);
    }
    printf("%.2f\n", sum);
}
// */
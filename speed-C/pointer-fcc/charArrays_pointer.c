// charArrays_pointer.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*understanding important of NULL char*/
/*
int main(void)
{
    char c[4] = {'J', 'O', 'H', 'N'}; // it has exactly same size as visible characters
                                      // no space for NULL char results in garbage value
                                      // so, sizeOfChar >= charactersCount + 1;
                                      // also lacking of NULL Value leads to wrong strlen count;

    char c[20] = {'J', 'O', 'H', 'N', '\0'}; // sizeOfChar >= charactersCount + 1; Size needs to be set EXPLICITLY
    char c[] = "John";                       // compiler autd-detects size; and size auto-sets IMPPLICITLY
                                             // in that case, (charactersCount+1)th character is '\0';

    printf("%s | length: %d | size: %zu\n", c, strlen(c), sizeof(c)); // strlen is count 4; it stops exactly before NULL Char
                                                                      // but size is what is set, size=20 if 'char c[20];
    return 0;
}
*/

/*charArrays and pointers*/
int main(void)
{
    char c1[6] = "Hello"; // string
    char *pointer = c1;
    pointer[1] = 'z'; // c1[1] | here c1 is the address
                      // pointer[1] | here pointer is the address

    printf("pointer[1] == c[1] | so, they both represent: %c\n", pointer[1]);
    printf("now, c1 = %s\n", c1); // pointer[1] goes to that address
                                  //  and replaces l with z;
                                  // no extra memory; no variable
                                  // just dereferencing
}



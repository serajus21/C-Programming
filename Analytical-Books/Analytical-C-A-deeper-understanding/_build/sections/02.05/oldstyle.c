/* oldstyle.c
   C as it was written before prototypes, still accepted until C23. */
#include <stdio.h>

int area();                     /* empty parentheses: arguments unchecked */

int main(void) {
    printf("%d\n", area(6, 7));
    printf("%d\n", area(6));    /* a mistake: one argument missing */
    return 0;
}

int area(w, h)                  /* a definition in the style of 1978 */
int w, h;
{
    return w * h;
}

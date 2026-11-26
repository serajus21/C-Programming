/* version.c
   Which edition of C is this compiler following?
   (Comments in this file use the old form, because C89 has no //.) */
#include <stdio.h>

int main(void) {
#if !defined(__STDC_VERSION__)
    puts("C89/C90: __STDC_VERSION__ is not defined");
#elif __STDC_VERSION__ > 201710L
    printf("C23 or later: %ld\n", (long)__STDC_VERSION__);
#elif __STDC_VERSION__ == 201710L
    puts("C17");
#elif __STDC_VERSION__ == 201112L
    puts("C11");
#elif __STDC_VERSION__ == 199901L
    puts("C99");
#else
    puts("C95 (C90 with Amendment 1)");
#endif
    return 0;
}

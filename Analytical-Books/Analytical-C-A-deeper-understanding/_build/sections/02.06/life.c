// life.c
// What runs before main starts, and after it returns.
#include <stdio.h>
#include <stdlib.h>

__attribute__((constructor))        // a GCC extension: run before main
static void before(void) {
    puts("1. before main: a constructor");
}

static void after(void) {
    puts("4. after main: a function registered with atexit");
}

int main(int argc, char *argv[]) {
    atexit(after);
    printf("2. main: argc = %d, argv[0] = %s\n", argc, argv[0]);
    printf("3. main: __STDC_HOSTED__ = %d\n", __STDC_HOSTED__);
    return 0;
}

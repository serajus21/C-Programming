// order.c
// What runs before main, and after it.
#include <stdio.h>
#include <stdlib.h>

__attribute__((constructor)) static void before(void) { puts("constructor: before main"); }
__attribute__((destructor))  static void after(void)  { puts("destructor: after exit's handlers"); }

static void bye(void) { puts("atexit handler: inside exit"); }

int main(void) {
    atexit(bye);
    puts("main");
    return 0;
}

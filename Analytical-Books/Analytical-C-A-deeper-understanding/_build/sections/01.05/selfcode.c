// selfcode.c
// On a von Neumann machine, a program can read its own instructions as
// ordinary bytes. Can it also change them?
#include <stdio.h>
#include <stdint.h>

int add(int a, int b) {
    return a + b;
}

int main(void) {
    // Turn the function's address into a byte address.
    // (Implementation-defined in C; GCC on Linux allows it.)
    unsigned char *code = (unsigned char *)(uintptr_t)add;

    printf("add() lives at %p\n", (void *)code);
    printf("its first bytes:");
    for (int i = 0; i < 4; ++i) {
        printf(" %02x", code[i]);
    }
    printf("\nadd(6, 7) = %d\n", add(6, 7));

    printf("now trying to overwrite the first byte...\n");
    fflush(stdout);
    code[0] = 0xC3;                     // write into our own code
    printf("it worked: the code was changed\n");
}

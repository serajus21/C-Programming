// check_toolchain.c
#include <stdio.h>

int main(void) {
    printf("C standard version: %ld\n", __STDC_VERSION__);
    printf("Compiler:           %s\n", __VERSION__);
    printf("Hosted environment: %d\n", __STDC_HOSTED__);
    printf("Size of int:        %zu bytes\n", sizeof(int));
}
// phases.c
// Which program complains? Build with -DSTAGE=1, 2, 3 or 4.
#if STAGE == 1
#include <stdoi.h>                      // preprocessor: no such header
#endif
#include <stdio.h>

void undefined_elsewhere(void);         // declared, never defined

int main(void) {
#if STAGE == 2
    int n = ;                           // compiler: not C
#elif STAGE == 3
    __asm__("movq %rax, %rbx, %rcx");   // assembler: no such instruction form
#elif STAGE == 4
    undefined_elsewhere();              // linker: no definition anywhere
#endif
    puts("built");
    return 0;
}

// stack.c
// What the kernel placed on the stack before _start ran.
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <elf.h>          // Elf64_auxv_t and the AT_ names
#include <sys/auxv.h>     // getauxval

extern char **environ;    // the environment, as the C library sees it

int main(int argc, char *argv[]) {
    printf("argc = %d at %p\n", argc, (void *)&argc);
    printf("argv = %p, argv[argc] = %p\n", (void *)argv, (void *)argv[argc]);
    char **envp = argv + argc + 1;                 // just past argv's NULL
    printf("envp = %p, environ = %p\n", (void *)envp, (void *)environ);
    char **p = envp;
    while (*p != NULL) ++p;                        // skip the environment
    Elf64_auxv_t *aux = (Elf64_auxv_t *)(p + 1);   // the auxv follows
    for (; aux->a_type != AT_NULL; ++aux) {
        switch (aux->a_type) {
        case AT_PHDR: case AT_PHNUM: case AT_PAGESZ: case AT_BASE:
        case AT_ENTRY: case AT_RANDOM: case AT_SYSINFO_EHDR: case AT_EXECFN:
            printf("auxv %2" PRIu64 ": 0x%" PRIx64 "\n",
                   (uint64_t)aux->a_type, (uint64_t)aux->a_un.a_val);
        }
    }
    printf("getauxval(AT_ENTRY) = 0x%lx, main = 0x%" PRIxPTR "\n",
           getauxval(AT_ENTRY), (uintptr_t)main);
    return 0;
}

// maps.c
// Where do code and data live? Ask the operating system.
#include <stdio.h>
#include <stdint.h>

int counter = 5;                        // a variable: data

int main(void) {
    printf("main    is at %#jx\n", (uintmax_t)(uintptr_t)main);
    printf("counter is at %#jx\n", (uintmax_t)(uintptr_t)&counter);

    FILE *m = fopen("/proc/self/maps", "r");    // this process's map
    char line[256];
    for (int i = 0; i < 5 && fgets(line, sizeof line, m); ++i) {
        printf("%.30s\n", line);        // address range and permissions
    }
    fclose(m);
}

// cet.c
// Report which control-flow protections are active for this process.
#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *f = fopen("/proc/self/status", "r");
    if (f == NULL) return 1;
    char line[256];
    while (fgets(line, sizeof line, f) != NULL)
        if (strncmp(line, "x86_Thread_features", 19) == 0)
            fputs(line, stdout);
    fclose(f);
    return 0;
}

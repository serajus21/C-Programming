// nullcheck.c
// A null-pointer check that comes too late.
#include <stddef.h>

int read_sensor(const int *p) {
    int value = *p;                 // use the pointer...
    if (p == NULL) {                // ...then check it
        return -1;
    }
    return value;
}

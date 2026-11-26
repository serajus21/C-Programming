// checked.c
// The price of one bounds check, counted in instructions.
#include <stddef.h>

// The C way: trust the caller to pass 0 <= i < n.
int get(const int *a, size_t n, size_t i) {
    (void)n;                        // n is not even looked at
    return a[i];
}

// The checked way: test the index first, and return 0 if it is outside.
int get_checked(const int *a, size_t n, size_t i) {
    if (i < n) {
        return a[i];
    }
    return 0;
}

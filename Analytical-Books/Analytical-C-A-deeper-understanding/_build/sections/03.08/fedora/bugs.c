// bugs.c
// Six small mistakes. How many does the compiler mention?
#include <stdio.h>

static int is_zero(int x) {
    if (x = 0)                          // meant: x == 0
        return 1;
    return 0;
}

static unsigned count_below(const int *a, int n, unsigned limit) {
    unsigned c = 0;
    for (int i = 0; i < n; ++i)
        if (a[i] < limit)               // int compared with unsigned
            ++c;
    return c;
}

static int sum(const int *a, int n) {
    int total;                          // never set to 0
    for (int i = 0; i < n; ++i)
        total += a[i];
    return total;
}

static int sign(int x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
}                                       // no return when x == 0

static int days(int month) {            // 1 = January
    int d = 31;
    switch (month) {
    case 2: d = 28;                     // forgot break: falls through
    case 4: case 6: case 9: case 11: d = 30; break;
    }
    return d;
}

int main(void) {
    int a[3] = {-1, 5, 7};
    printf("%d %u %d %d %d\n", is_zero(0), count_below(a, 3, 6),
           sum(a, 3), sign(0), days(2));
    printf("%d\n", 3.5);                // wrong conversion for a double
    return 0;
}

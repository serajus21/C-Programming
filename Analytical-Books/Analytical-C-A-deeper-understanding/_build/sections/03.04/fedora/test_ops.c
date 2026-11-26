// test_ops.c
// The same tests, whatever level ops.c was compiled at.
#include <stdio.h>

int times10(int x);
unsigned div10(unsigned x);
int sum_to(int n);

int main(void) {
    unsigned long long h = 0;          // a running "fingerprint" of all results
    for (int x = -100000; x <= 100000; ++x) {
        h = h * 31 + (unsigned)times10(x);
    }
    for (unsigned x = 0; x < 3000000; x += 7) {
        h = h * 31 + div10(x);
    }
    for (int n = 0; n <= 20000; ++n) {
        h = h * 31 + (unsigned)sum_to(n);
    }
    printf("%llx\n", h);
    return 0;
}

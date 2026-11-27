#include <stdio.h>
const int primes[4] = {2, 3, 5, 7};
int main(void) {
    int *p = (int *)&primes[2];   // casting away const: undefined behavior
    *p = 9;
    printf("%d\n", primes[2]);
    return 0;
}

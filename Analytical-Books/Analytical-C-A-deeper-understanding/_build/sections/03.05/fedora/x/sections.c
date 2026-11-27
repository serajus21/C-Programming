// sections.c
// One object of each kind, to see where each one lands.
#include <stdio.h>

int counter = 42;                    // a global with an initializer
int zeros[1000];                     // a global without one
const int primes[4] = {2, 3, 5, 7};  // a global constant
static int hidden = 7;               // visible only in this file
extern int elsewhere;                // declared here, defined elsewhere

static int helper(int x) {           // a function visible only in this file
    static int calls;                // keeps its value between calls
    ++calls;
    return x + calls + hidden;
}

int main(void) {
    printf("%s %d %d %d\n", "sections", counter, primes[2], helper(zeros[0]));
    return elsewhere;
}

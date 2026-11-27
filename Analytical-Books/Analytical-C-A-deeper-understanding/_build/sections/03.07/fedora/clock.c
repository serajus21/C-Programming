// clock.c
// Ask for the time three times. Does the kernel hear about it?
#include <stdio.h>
#include <time.h>

int main(void) {
    struct timespec t;
    for (int i = 0; i < 3; ++i) {
        timespec_get(&t, TIME_UTC);                 // standard C since C11
        printf("%lld.%09ld\n", (long long)t.tv_sec, t.tv_nsec);
    }
    return 0;
}

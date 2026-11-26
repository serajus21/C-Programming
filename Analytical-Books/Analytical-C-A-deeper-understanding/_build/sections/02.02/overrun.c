// overrun.c
// C trusts the programmer: an index one past the end is not caught.
#include <stdio.h>

struct record {
    int readings[4];
    int checksum;
};

void store(struct record *r, int i, int value) {
    r->readings[i] = value;             // no check that 0 <= i < 4
}

int main(void) {
    struct record r = { {0, 0, 0, 0}, 1234 };
    for (int i = 0; i <= 4; ++i) {      // one step too many: i reaches 4
        store(&r, i, 7);
    }
    printf("checksum = %d\n", r.checksum);
}

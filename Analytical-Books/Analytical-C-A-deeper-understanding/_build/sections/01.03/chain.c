// chain.c  (Experiment 01.03-3)
// How many stages in a row does a carry travel through?
#include <stdio.h>

int longest_chain(int x, int y) {
    int carry = 0;
    int run = 0;
    int longest = 0;
    for (int i = 0; i < 8; ++i) {
        int a = (x >> i) & 1;
        int b = (y >> i) & 1;
        carry = (a & b) | (carry & (a ^ b));
        if (carry) {
            ++run;
            if (run > longest) {
                longest = run;
            }
        } else {
            run = 0;
        }
    }
    return longest;
}

int main(void) {
    printf("255 + 1   : %d\n", longest_chain(255, 1));
    printf(" 15 + 1   : %d\n", longest_chain(15, 1));
    printf("128 + 128 : %d\n", longest_chain(128, 128));
    printf(" 85 + 170 : %d\n", longest_chain(85, 170));
    long count[9] = {0};
    for (int x = 0; x < 256; ++x) {
        for (int y = 0; y < 256; ++y) {
            ++count[longest_chain(x, y)];
        }
    }
    for (int k = 0; k <= 8; ++k) {
        printf("longest chain %d: %5ld pairs\n", k, count[k]);
    }
}

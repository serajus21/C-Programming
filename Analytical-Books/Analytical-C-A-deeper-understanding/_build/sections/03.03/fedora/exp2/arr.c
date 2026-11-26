int a[] = {
#include "nums.txt"
};
#include <stdio.h>
int main(void) { printf("%zu\n", sizeof a / sizeof a[0]); return 0; }

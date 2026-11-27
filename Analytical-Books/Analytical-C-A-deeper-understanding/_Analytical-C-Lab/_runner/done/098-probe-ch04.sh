#!/bin/bash
# Readiness probe for Chapter 04
echo "== whoami: $(whoami)  host: $(hostname)"
gcc --version | head -1
clang --version | head -1
avr-gcc --version | head -1
echo '#include <stdckdint.h>
#include <stdio.h>
#include <limits.h>
int main(void){int r; bool o = ckd_add(&r, INT_MAX, 1); printf("%d %d\n", o, r);}' > /tmp/ck04.c
gcc -std=c23 -Wall -Wextra -pedantic -fsanitize=undefined /tmp/ck04.c -o /tmp/ck04 && /tmp/ck04
echo "== limits"; printf '#include <limits.h>\nINT_MIN INT_MAX UINT_MAX LLONG_MIN\n' | gcc -E -P -x c - | tail -1

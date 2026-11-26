// ops.c
// Three small functions, to watch the optimizer at work.
int times10(int x) {
    return x * 10;
}

unsigned div10(unsigned x) {
    return x / 10;
}

int sum_to(int n) {
    int s = 0;
    for (int i = 1; i <= n; ++i) {
        s += i;
    }
    return s;
}

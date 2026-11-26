// length.c: the same function in C
int length(char *s) {
    int n = 0;
    while (s[n] != '\0') {
        n++;
    }
    return n;
}

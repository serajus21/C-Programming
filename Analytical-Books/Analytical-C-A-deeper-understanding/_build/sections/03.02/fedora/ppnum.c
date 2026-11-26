// ppnum.c
// A preprocessing number is not yet a number.
int main(void) {
    int a = 0x1E + 1;    // three tokens: 0x1E, +, 1
    int b = 0x1E+1;      // one preprocessing token: 0x1E+1
    return a + b;
}

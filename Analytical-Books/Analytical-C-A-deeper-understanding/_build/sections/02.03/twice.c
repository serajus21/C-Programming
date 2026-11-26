// twice.c
// Compute the same result twice and compare, to detect a fault
// (a common idea in software meant to survive radiation upsets).
static int compute(int x) {
    return x * x + 3 * x + 1;
}

int checked_compute(int x, int *fault) {
    int a = compute(x);
    int b = compute(x);             // the same calculation, a second time
    *fault = (a != b);              // 1 if the two results disagree
    return a;
}

int checked_compute_v(int x, int *fault) {
    volatile int a = compute(x);    // volatile: both values must really
    volatile int b = compute(x);    // be stored and read back
    *fault = (a != b);
    return a;
}

int checked_compute_vin(int x, int *fault) {
    volatile int in = x;            // volatile input: read it twice, and
    int a = compute(in);            // the computation must really be done
    int b = compute(in);            // twice, once from each read
    *fault = (a != b);
    return a;
}

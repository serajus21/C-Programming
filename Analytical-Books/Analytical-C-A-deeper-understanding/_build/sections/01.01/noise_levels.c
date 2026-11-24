// noise_levels.c
// How often is a noisy voltage misread, with 2, 4 or 10 levels in 0-5 V?
#include <stdio.h>
#include <stdint.h>

static uint32_t state = 2463534242u;    // fixed seed: same output every run

static double uniform(void) {           // a number from 0 up to (not incl.) 1
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state / 4294967296.0;
}

static double noise(double sigma) {     // roughly bell-shaped noise
    double sum = 0.0;
    for (int k = 0; k < 12; ++k) {
        sum += uniform();
    }
    return (sum - 6.0) * sigma;
}

int main(void) {
    const double full_scale = 5.0;            // volts
    const double sigma = 0.4;                 // size of the noise, in volts
    const long trials = 1000000;
    const int levels_to_try[] = {2, 4, 10};

    for (int t = 0; t < 3; ++t) {
        int levels = levels_to_try[t];
        double step = full_scale / (levels - 1);   // spacing between levels
        long errors = 0;
        for (long i = 0; i < trials; ++i) {
            int sent = (int)(uniform() * levels);  // a random level
            double volts = sent * step + noise(sigma);
            int read = (int)(volts / step + 0.5);  // nearest level
            if (read < 0) {
                read = 0;
            }
            if (read > levels - 1) {
                read = levels - 1;
            }
            if (read != sent) {
                ++errors;
            }
        }
        printf("%2d levels, spacing %.3f V: %7ld errors in %ld (%.4f %%)\n",
               levels, step, errors, trials, 100.0 * errors / trials);
    }
}

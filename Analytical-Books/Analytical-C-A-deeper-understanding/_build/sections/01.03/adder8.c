// adder8.c
// An 8-bit ripple-carry adder and subtractor built from logic gates,
// checked against C's own arithmetic for every possible pair of inputs.
#include <stdio.h>

int flag_c, flag_z, flag_n, flag_v;     // the status flags

int sum_bit(int a, int b, int cin) {    // full adder: sum output
    return (a ^ b) ^ cin;
}

int carry_bit(int a, int b, int cin) {  // full adder: carry output
    return (a & b) | (cin & (a ^ b));
}

int alu_add(int x, int y, int subtract) {   // x and y are 0..255
    int carry = subtract;               // carry into bit 0
    int carry_into_top = 0;
    int result = 0;
    for (int i = 0; i < 8; ++i) {
        int a = (x >> i) & 1;           // bit i of x
        int b = ((y >> i) & 1) ^ subtract;  // flipped when subtracting
        if (i == 7) {
            carry_into_top = carry;
        }
        result = result | (sum_bit(a, b, carry) << i);
        carry = carry_bit(a, b, carry);
    }
    flag_c = carry;
    flag_z = (result == 0);
    flag_n = (result >> 7) & 1;
    flag_v = carry_into_top ^ carry;
    return result;
}

int as_signed(int x) {                  // read an 8-bit pattern as -128..127
    if (x >= 128) {
        return x - 256;
    }
    return x;
}

int main(void) {
    long mismatches = 0;
    for (int x = 0; x < 256; ++x) {
        for (int y = 0; y < 256; ++y) {
            int s = alu_add(x, y, 0);
            int sum = x + y;
            int ssum = as_signed(x) + as_signed(y);
            if (s != sum % 256 || flag_c != (sum > 255)
                    || flag_v != (ssum < -128 || ssum > 127)) {
                ++mismatches;
            }
            int d = alu_add(x, y, 1);
            int sdiff = as_signed(x) - as_signed(y);
            if (d != (x - y + 256) % 256 || flag_c != (x >= y)
                    || flag_v != (sdiff < -128 || sdiff > 127)) {
                ++mismatches;
            }
        }
    }
    printf("Checked 131072 additions and subtractions: %ld mismatches\n\n",
           mismatches);

    const int xs[]  = {6, 255, 100, 200, 5, 3};
    const int ys[]  = {7,   1,  50, 100, 3, 5};
    const int sub[] = {0,   0,   0,   0, 1, 1};
    printf("  operation   result | C Z N V | unsigned | signed\n");
    for (int k = 0; k < 6; ++k) {
        int r = alu_add(xs[k], ys[k], sub[k]);
        printf("%4d %c %3d  = %3d    | %d %d %d %d |   %3d    | %4d\n",
               xs[k], sub[k] ? '-' : '+', ys[k], r,
               flag_c, flag_z, flag_n, flag_v, r, as_signed(r));
    }
}

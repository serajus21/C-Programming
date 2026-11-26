// libcost.c
// What does the library add? Build with -DSTEP=0, 1, 2 or 3 and compare sizes.
#include <stdio.h>
#include <avr/io.h>

static int uart_putchar(char c, FILE *f) {
    (void)f;
    while (!(UCSR0A & (1 << UDRE0))) {}
    UDR0 = c;
    return 0;
}
static FILE uart = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

int main(void) {
    UCSR0A = (1 << U2X0); UBRR0 = 16;       // about 115,200 baud
    UCSR0B = (1 << TXEN0);
    stdout = &uart;
    volatile int    n = 42;                 // volatile: computed at run time
    volatile double x = 3.25;
#if STEP == 0
    (void)n; (void)x;                       // no library function called
#elif STEP == 1
    (void)x;
    uart_putchar((char)('0' + n % 10), NULL);   // our own code; % needs libgcc
#elif STEP == 2
    (void)x;
    printf("%d\n", n);                      // the library's printf, integers only
#elif STEP == 3
    printf("%d %.2f\n", n, x);              // printf with floating point
#endif
    for (;;) {}
}

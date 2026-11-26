// steps.c
// One source file, built unchanged for two very different machines.
#include <stdio.h>
#include <stdint.h>

#ifdef __AVR__          // Only for the bare AVR: connect printf to the UART.
#include <avr/io.h>
#include <avr/sleep.h>
static int uart_putchar(char c, FILE *f) {
    (void)f;
    while (!(UCSR0A & (1 << UDRE0))) {}     // wait until the UART is free
    UDR0 = c;                               // send one character
    return 0;
}
static FILE uart = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
#endif

int main(void) {
#ifdef __AVR__
    UCSR0A = (1 << U2X0); UBRR0 = 16;       // about 115,200 baud (double speed)
    UCSR0B = (1 << TXEN0);                  // switch the transmitter on
    stdout = &uart;
#endif
    char   c[2];
    short  h[2];
    int    i[2];
    long   l[2];
    long long q[2];
    double d[2];

    printf("bytes in: char %u, short %u, int %u, long %u, long long %u, double %u, pointer %u\n",
           (unsigned)sizeof c[0], (unsigned)sizeof h[0], (unsigned)sizeof i[0],
           (unsigned)sizeof l[0], (unsigned)sizeof q[0], (unsigned)sizeof d[0],
           (unsigned)sizeof &i[0]);

    // How far, in bytes, is "the next element" from this one?
    printf("p + 1 moves: char %d, short %d, int %d, long %d, long long %d, double %d bytes\n",
           (int)((char *)(&c[0] + 1) - (char *)&c[0]),
           (int)((char *)(&h[0] + 1) - (char *)&h[0]),
           (int)((char *)(&i[0] + 1) - (char *)&i[0]),
           (int)((char *)(&l[0] + 1) - (char *)&l[0]),
           (int)((char *)(&q[0] + 1) - (char *)&q[0]),
           (int)((char *)(&d[0] + 1) - (char *)&d[0]));

    printf("i[0] is at byte address 0x%lx, i[1] at 0x%lx\n",
           (unsigned long)(uintptr_t)&i[0], (unsigned long)(uintptr_t)&i[1]);

#ifdef __AVR__
    while (!(UCSR0A & (1 << TXC0))) {}      // let the last character go out
    __asm__ volatile ("cli");               // then stop the simulation
    sleep_mode();
#endif
    return 0;
}

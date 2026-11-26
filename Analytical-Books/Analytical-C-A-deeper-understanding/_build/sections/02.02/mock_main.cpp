// verification harness only: a minimal stand-in for Arduino's Serial over the UART
#include <avr/io.h>
#include <stdint.h>
struct SerialMock {
    void tx(char c) { while (!(UCSR0A & (1 << UDRE0))) {} UDR0 = c; }
    void begin(long) { UCSR0A = (1 << U2X0); UBRR0 = 16; UCSR0B = (1 << TXEN0); UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); }
    void print(const char *s) { while (*s) tx(*s++); }
    void print(long v) { char b[12]; int n = 0; bool neg = v < 0; unsigned long u = neg ? -(unsigned long)v : (unsigned long)v;
        if (u == 0) b[n++] = '0'; while (u) { b[n++] = '0' + u % 10; u /= 10; } if (neg) tx('-'); while (n) tx(b[--n]); }
    void println() { tx('\r'); tx('\n'); }
    void println(const char *s) { print(s); println(); }
} Serial;
static void delay(unsigned long) {}
#include "choices.ino"
int main(void) {
    setup();
    while (!(UCSR0A & (1 << TXC0))) {}
    __asm__ volatile("cli"); SMCR = (1 << SE); __asm__ volatile("sleep");
    for (;;) {}
}

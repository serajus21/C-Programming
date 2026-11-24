// verification harness only: a minimal stand-in for Arduino's Serial over the UART
#include <avr/io.h>
#include <stdint.h>
struct SerialMock {
    void tx(char c) { while (!(UCSR0A & (1 << UDRE0))) {} UDR0 = c; }
    void begin(long) { UBRR0 = 8; UCSR0B = (1 << TXEN0); UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); }
    void print(const char *s) { while (*s) tx(*s++); }
    void print(int v) { char b[8]; int n = 0; if (v == 0) b[n++] = '0'; while (v) { b[n++] = '0' + v % 10; v /= 10; } while (n) tx(b[--n]); }
    void println() { tx('\r'); tx('\n'); }
} Serial;
#include "flags.ino"
int main(void) {
    setup();
    while (!(UCSR0A & (1 << TXC0))) {}
    __asm__ volatile("cli"); SMCR = (1 << SE); __asm__ volatile("sleep");
    for (;;) {}
}

// verification harness only: a minimal stand-in for Arduino's Serial
#include <avr/io.h>
#include <stdint.h>
typedef uint8_t byte;
enum { DEC = 10, HEX = 16 };
struct SerialMock {
    void tx(char c) { while (!(UCSR0A & (1 << UDRE0))) {} UDR0 = c; }
    void begin(long) { UBRR0 = 103; UCSR0B = (1 << TXEN0); UCSR0C = 6; }
    void print(const char *s) { while (*s) tx(*s++); }
    void print(char c) { tx(c); }
    void print(unsigned v, int base = DEC) { char b[8]; int n = 0; if (v == 0) b[n++] = '0';
        while (v) { int d = v % base; b[n++] = d < 10 ? '0' + d : 'A' + d - 10; v /= base; } while (n) tx(b[--n]); }
    void print(unsigned char v, int base = DEC) { print((unsigned)v, base); }
    void println() { tx('\r'); tx('\n'); }
    template <class T> void println(T v) { print(v); println(); }
    void println(unsigned v, int base) { print(v, base); println(); }
    void println(unsigned char v) { print(v); println(); }
} Serial;
#include "selfread.ino"
int main(void) {
    setup();
    while (!(UCSR0A & (1 << TXC0))) {}
    __asm__ volatile("cli"); SMCR = (1 << SE); __asm__ volatile("sleep");
    for (;;) {}
}

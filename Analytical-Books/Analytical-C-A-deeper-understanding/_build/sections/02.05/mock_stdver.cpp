// verification harness only: minimal stand-ins for Arduino's Serial and delay
#include <avr/io.h>
#include <stdint.h>
struct SerialMock {
    void tx(char c) { while (!(UCSR0A & (1 << UDRE0))) {} UDR0 = c; }
    void begin(long) { UCSR0A = (1 << U2X0); UBRR0 = 16; UCSR0B = (1 << TXEN0); UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); }
    void print(const char *s) { while (*s) tx(*s++); }
    void print(unsigned long v) { char b[12]; int n = 0; if (v == 0) b[n++] = '0'; while (v) { b[n++] = '0' + v % 10; v /= 10; } while (n) tx(b[--n]); }
    void print(long v) { if (v < 0) { tx('-'); print((unsigned long)(-v)); } else print((unsigned long)v); }
    void print(int v) { print((long)v); }
    void println(const char *s) { print(s); tx('\r'); tx('\n'); }
    void println(unsigned long v) { print(v); tx('\r'); tx('\n'); }
    void println(int v) { print(v); tx('\r'); tx('\n'); }
    void println(long v) { print(v); tx(0x0D); tx(0x0A); }
    void flush() { while (!(UCSR0A & (1 << TXC0))) {} }
} Serial;
static void delay(unsigned long) {}
#include "stdver.ino"
int main(void) {
    UCSR0A = (1 << TXC0);
    setup();
    while (!(UCSR0A & (1 << TXC0))) {}
    __asm__ volatile("cli"); SMCR = (1 << SE); __asm__ volatile("sleep");
    for (;;) {}
}

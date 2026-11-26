// verification harness only: minimal stand-ins for Arduino's Serial, delay and micros
#include <avr/io.h>
#include <stdint.h>
struct SerialMock {
    void tx(char c) { while (!(UCSR0A & (1 << UDRE0))) {} UDR0 = c; }
    void begin(long) { UCSR0A = (1 << U2X0); UBRR0 = 16; UCSR0B = (1 << TXEN0); UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); }
    void print(const char *s) { while (*s) tx(*s++); }
    void print(unsigned long v) { char b[12]; int n = 0; if (v == 0) b[n++] = '0'; while (v) { b[n++] = '0' + v % 10; v /= 10; } while (n) tx(b[--n]); }
    void println(const char *s) { print(s); tx('\r'); tx('\n'); }
} Serial;
static void delay(unsigned long) {}
static unsigned long micros() { return (unsigned long)TCNT1 * 64; }   // Timer 1 at clock/1024
#include "delayloop.ino"
int main(void) {
    TCCR1B = (1 << CS12) | (1 << CS10);
    setup();
    while (!(UCSR0A & (1 << TXC0))) {}
    __asm__ volatile("cli"); SMCR = (1 << SE); __asm__ volatile("sleep");
    for (;;) {}
}

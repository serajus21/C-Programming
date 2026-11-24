// verification only: run on simavr, print SREG after ADD and SUB
#include <avr/io.h>
#include <stdint.h>
static void tx(char c) { while (!(UCSR0A & (1 << UDRE0))) {} UDR0 = c; }
static void hex2(uint8_t v) { const char *h = "0123456789ABCDEF"; tx(h[v >> 4]); tx(h[v & 15]); }
static void bits(uint8_t v) { for (int i = 7; i >= 0; --i) tx((v >> i) & 1 ? '1' : '0'); }
static void report(char op, uint8_t a, uint8_t b, uint8_t r, uint8_t s) {
    hex2(a); tx(op); hex2(b); tx('='); hex2(r); tx(' '); tx('S'); tx('R'); tx('E'); tx('G'); tx('='); bits(s); tx('\r'); tx('\n');
}
static void test_add(uint8_t a, uint8_t b) {
    uint8_t r = a, s;
    asm volatile("add %0, %2\n\tin %1, __SREG__" : "+r"(r), "=r"(s) : "r"(b));
    report('+', a, b, r, s);
}
static void test_sub(uint8_t a, uint8_t b) {
    uint8_t r = a, s;
    asm volatile("sub %0, %2\n\tin %1, __SREG__" : "+r"(r), "=r"(s) : "r"(b));
    report('-', a, b, r, s);
}
int main(void) {
    UBRR0 = 8; UCSR0B = (1 << TXEN0); UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    test_add(6, 7); test_add(255, 1); test_add(100, 50); test_add(200, 100);
    test_sub(5, 3); test_sub(3, 5);
    while (!(UCSR0A & (1 << TXC0))) {}
    __asm__ volatile("cli"); SMCR = (1 << SE); __asm__ volatile("sleep");
    for (;;) {}
}

// verification harness: time delay_plain and delay_volatile with Timer 1
#include <stdio.h>
#include <avr/io.h>
#include <stdint.h>
void delay_plain(void);
void delay_volatile(void);
static uint16_t ticks(void (*f)(void)) {
    TCCR1B = 0; TCNT1 = 0;
    TCCR1B = (1 << CS12) | (1 << CS10);     // clock / 1024: one tick = 64 us
    f();
    uint16_t t = TCNT1;                     // read before stopping the clock
    TCCR1B = 0;
    return t;
}
int main(void) {
    uint16_t a = ticks(delay_plain), b = ticks(delay_volatile);
    printf("plain: %u ticks, volatile: %u ticks (1 tick = 64 us)\n", a, b);
}

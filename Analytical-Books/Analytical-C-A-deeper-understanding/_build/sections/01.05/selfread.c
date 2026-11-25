// selfread.c  (simulator version)
// The AVR reads its own machine code, as data, through LPM.
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <stdio.h>

static int uart_putchar(char c, FILE *f) {      // send one character
    (void)f;
    while (!(UCSR0A & (1 << UDRE0))) {}
    UDR0 = c;
    return 0;
}
static FILE out = FDEV_SETUP_STREAM(uart_putchar, NULL,
                                    _FDEV_SETUP_WRITE);

__attribute__((noinline))
uint8_t add8(uint8_t a, uint8_t b) {
    return a + b;
}

int main(void) {
    UCSR0B = 1 << TXEN0;                        // enable the transmitter
    stdout = &out;                              // printf goes to the UART
    uint16_t word_addr = (uint16_t)add8;        // flash counts words
    uint16_t byte_addr = word_addr * 2;         // two bytes per word
    printf("add8 word %04X byte %04X:", word_addr, byte_addr);
    for (uint8_t i = 0; i < 4; ++i) {
        printf(" %02X", pgm_read_byte(byte_addr + i));  // LPM
    }
    printf(" sum=%u\n", add8(6, 7));
    cli();                                      // end of the simulation
    SMCR = 1 << SE;
    sleep_cpu();
}

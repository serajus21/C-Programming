// verification harness only: connect stdout to the ATmega328P's UART
// before main runs, and stop the simulator after main returns.
#include <avr/io.h>
#include <avr/sleep.h>
#include <stdio.h>
static int uart_putchar(char c, FILE *f) {
    (void)f;
    while (!(UCSR0A & (1 << UDRE0))) {}
    UDR0 = c;
    return 0;
}
static FILE uart = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
__attribute__((section(".init8"), naked, used)) static void uart_init(void) {
    UCSR0A = (1 << U2X0); UBRR0 = 16;
    UCSR0B = (1 << TXEN0);
    stdout = &uart;
}
__attribute__((section(".fini1"), naked, used)) static void stop(void) {
    while (!(UCSR0A & (1 << TXC0))) {}
    __asm__ volatile ("cli");
    sleep_mode();
}

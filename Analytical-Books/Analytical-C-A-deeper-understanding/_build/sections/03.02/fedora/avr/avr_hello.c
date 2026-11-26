// avr_hello.c  (ATmega328P, bare metal)
// hello, world on a chip with no screen: each character is sent
// through the UART, the serial port the Uno's USB cable carries.
#include <avr/io.h>

static void send(char c) {
    while (!(UCSR0A & (1 << UDRE0))) { }   // wait until the UART is free
    UDR0 = c;                              // hand it one character
}

int main(void) {
    UCSR0A = (1 << U2X0);                  // 115200 baud at 16 MHz:
    UBRR0 = 16;                            //   see §37.04
    UCSR0B = (1 << TXEN0);                 // switch the transmitter on
    for (const char *p = "hello, world\r\n"; *p != '\0'; ++p) {
        send(*p);
    }
    for (;;) { }                           // nowhere to return to
}

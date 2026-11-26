// avr_verbose.c  (ATmega328P, bare metal)
// avr_hello.c with 60 lines of comment and a 65-character name.
// hello, world on a chip with no screen: each character is sent
// through the UART, the serial port the Uno's USB cable carries.
#include <avr/io.h>
/*
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
   This line is a comment. It explains nothing and costs nothing.
*/

static void send_one_character_through_the_universal_asynchronous_transmitter(char c) {
    while (!(UCSR0A & (1 << UDRE0))) { }   // wait until the UART is free
    UDR0 = c;                              // hand it one character
}

int main(void) {
    UCSR0A = (1 << U2X0);                  // about 115200 baud at 16 MHz:
    UBRR0 = 16;                            //   see §37.04
    UCSR0B = (1 << TXEN0);                 // switch the transmitter on
    for (const char *p = "hello, world\r\n"; *p != '\0'; ++p) {
        send_one_character_through_the_universal_asynchronous_transmitter(*p);
    }
    for (;;) { }                           // nowhere to return to
}

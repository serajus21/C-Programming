// selfread.ino
// The Uno reads its own machine code out of flash, as ordinary data.
#include <avr/pgmspace.h>

__attribute__((noinline))       // keep add8 a real, separate function
byte add8(byte a, byte b) {
  return a + b;
}

volatile byte x = 6, y = 7;     // volatile: the compiler may not precompute

void setup() {
  Serial.begin(9600);
  uint16_t word_addr = (uint16_t)add8;  // the AVR counts flash in words
  uint16_t byte_addr = word_addr * 2;   // ...two bytes per word
  Serial.print("add8 starts at flash byte 0x");
  Serial.println(byte_addr, HEX);
  Serial.print("its first four bytes:");
  for (byte i = 0; i < 4; ++i) {
    byte b = pgm_read_byte(byte_addr + i);  // LPM: read flash as data
    Serial.print(b < 16 ? " 0" : " ");
    Serial.print(b, HEX);
  }
  Serial.println();
  Serial.print("add8(6, 7) = ");
  Serial.println(add8(x, y));
}

void loop() {}

// choices.ino  (Arduino Uno or ESP32)
// The Arduino version of Listing 02.02-5: ask each board the same questions.
#include <limits.h>

void line(const char *label, long value) {
  Serial.print(label);
  Serial.print(value);
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.print("plain char is: ");
  Serial.println(CHAR_MIN < 0 ? "signed" : "unsigned");
  line("bytes in an int: ", (long)sizeof(int));
  line("largest int: ", (long)INT_MAX);
  char c = (char)200;
  line("(char)200 reads back as: ", (long)c);
  int n = -7;
  line("-7 >> 1 gives: ", (long)(n >> 1));
  line("-7 / 2 gives: ", (long)(n / 2));
  line("-7 % 2 gives: ", (long)(n % 2));
}

void loop() {}

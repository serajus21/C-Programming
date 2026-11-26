// delayloop.ino  (Arduino Uno or ESP32)
// Time a do-nothing loop, with and without volatile.
void delay_plain() {
  for (uint32_t i = 0; i < 200000; ++i) { }
}

void delay_volatile() {
  for (volatile uint32_t i = 0; i < 200000; ++i) { }
}

void setup() {
  Serial.begin(115200);
  delay(500);
  unsigned long t0 = micros();
  delay_plain();
  unsigned long t1 = micros();
  delay_volatile();
  unsigned long t2 = micros();
  Serial.print("plain loop: ");
  Serial.print(t1 - t0);
  Serial.println(" us");
  Serial.print("volatile loop: ");
  Serial.print(t2 - t1);
  Serial.println(" us");
}

void loop() {}

// normal.ino  (Arduino Uno)
// An ordinary sketch: Arduino's own main() calls setup() and loop().
void setup() {
  Serial.begin(115200);
  Serial.println("setup(), called by Arduino's main() after init()");
  unsigned long t0 = millis();
  for (volatile long i = 0; i < 100000; ++i) { }   // waste some time
  Serial.print("millis() before and after the wait: ");
  Serial.print(t0);
  Serial.print(" ");
  Serial.println(millis());
}

void loop() {}

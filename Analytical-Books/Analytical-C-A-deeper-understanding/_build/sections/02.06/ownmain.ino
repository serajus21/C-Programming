// ownmain.ino  (Arduino Uno)
// The same work, in a sketch that defines main() itself.
int main(void) {
  Serial.begin(115200);
  Serial.println("main(), defined by the sketch: init() never ran");
  unsigned long t0 = millis();
  for (volatile long i = 0; i < 100000; ++i) { }   // waste some time
  Serial.print("millis() before and after the wait: ");
  Serial.print(t0);
  Serial.print(" ");
  Serial.println(millis());
  Serial.flush();
  for (;;) { }
}

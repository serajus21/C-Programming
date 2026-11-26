// ub.ino  (Arduino Uno or ESP32)
// Ask the processor in front of you two questions C leaves undefined.
void setup() {
  Serial.begin(115200);
  delay(500);

  volatile int n = 32;              // volatile: decided only when the code runs
  uint32_t x = 1;
  Serial.print("1 << 32 = ");
  Serial.println((unsigned long)(x << n));

  volatile int a = 7, b = 0;
  Serial.println("dividing 7 by 0 ...");
  Serial.flush();                   // let the message leave before the risk
  Serial.print("7 / 0 = ");
  Serial.println(a / b);
}

void loop() {}

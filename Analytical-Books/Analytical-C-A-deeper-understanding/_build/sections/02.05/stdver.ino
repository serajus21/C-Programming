// stdver.ino  (Arduino Uno or ESP32)
// Which editions do the board's two compilers follow?
extern "C" long c_version(void);    // defined in cver.c, compiled as C

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.print("C++ (this sketch): ");
  Serial.println(__cplusplus);
  Serial.print("C   (cver.c):      ");
  Serial.println(c_version());
}

void loop() {}

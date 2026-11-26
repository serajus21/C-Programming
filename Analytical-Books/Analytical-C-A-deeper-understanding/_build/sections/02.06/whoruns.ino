// whoruns.ino  (ESP32)
// Which FreeRTOS task, on which core, runs setup() and loop()?
void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.printf("setup() runs in task \"%s\" on core %d\n",
                pcTaskGetName(NULL), xPortGetCoreID());
}

void loop() {
  Serial.printf("loop()  runs in task \"%s\" on core %d\n",
                pcTaskGetName(NULL), xPortGetCoreID());
  delay(2000);
}

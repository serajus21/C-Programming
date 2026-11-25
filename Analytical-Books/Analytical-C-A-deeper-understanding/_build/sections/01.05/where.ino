// where.ino  (ESP32)
// Where does the ESP32 keep code and data? Print some addresses.
int counter = 5;                         // a variable
const char message[] = "hello";          // constant data

int IRAM_ATTR fast_add(int a, int b) {   // code placed in internal RAM
  return a + b;
}

int slow_add(int a, int b) {             // code left in flash
  return a + b;
}

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.printf("slow_add (code, flash): 0x%08X\n",
                (unsigned)(uintptr_t)slow_add);
  Serial.printf("fast_add (code, IRAM):  0x%08X\n",
                (unsigned)(uintptr_t)fast_add);
  Serial.printf("counter  (data, DRAM):  0x%08X\n",
                (unsigned)(uintptr_t)&counter);
  Serial.printf("message  (const data):  0x%08X\n",
                (unsigned)(uintptr_t)message);
  Serial.println(fast_add(6, 7) + slow_add(0, 0));
}

void loop() {}

// xtensa_bytes.ino  (ESP32)
// Print the first bytes of a function's machine code on the ESP32.
int IRAM_ATTR add_int(int a, int b) {   // placed in instruction RAM
  return a + b;
}

void setup() {
  Serial.begin(115200);
  delay(500);
  uintptr_t where = (uintptr_t)add_int;
  Serial.printf("add_int is at 0x%08X\n", (unsigned)where);
  // Instruction RAM can be read only as whole, aligned 32-bit words.
  const volatile uint32_t *word = (const volatile uint32_t *)where;
  Serial.print("first 8 bytes:");
  for (int i = 0; i < 2; ++i) {
    uint32_t w = word[i];
    for (int b = 0; b < 4; ++b) {       // lowest address first
      Serial.printf(" %02X", (unsigned)((w >> (8 * b)) & 0xFF));
    }
  }
  Serial.printf("\nadd_int(6, 7) = %d\n", add_int(6, 7));
}

void loop() {}

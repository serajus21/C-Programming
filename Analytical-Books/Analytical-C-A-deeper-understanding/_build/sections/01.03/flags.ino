// flags.ino  (Arduino Uno)
// Run one AVR ADD or SUB instruction and print the status register after it.
uint8_t result;
uint8_t sreg;

void add_and_read(uint8_t a, uint8_t b) {
    result = a;
    asm volatile("add %0, %2\n\t"
                 "in  %1, __SREG__"
                 : "+r" (result), "=r" (sreg)
                 : "r" (b));
}

void sub_and_read(uint8_t a, uint8_t b) {
    result = a;
    asm volatile("sub %0, %2\n\t"
                 "in  %1, __SREG__"
                 : "+r" (result), "=r" (sreg)
                 : "r" (b));
}

void show(uint8_t a, const char *op, uint8_t b) {
    Serial.print(a);
    Serial.print(op);
    Serial.print(b);
    Serial.print(" = ");
    Serial.print(result);
    Serial.print("    I T H S V N Z C = ");
    for (int bit = 7; bit >= 0; --bit) {
        Serial.print((sreg >> bit) & 1);
        Serial.print(" ");
    }
    Serial.println();
}

void setup(void) {
    Serial.begin(9600);
    add_and_read(6, 7);
    show(6, " + ", 7);
    add_and_read(255, 1);
    show(255, " + ", 1);
    add_and_read(100, 50);
    show(100, " + ", 50);
    add_and_read(200, 100);
    show(200, " + ", 100);
    sub_and_read(5, 3);
    show(5, " - ", 3);
    sub_and_read(3, 5);
    show(3, " - ", 5);
}

void loop(void) {
}

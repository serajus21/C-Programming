// nand_latch.ino  (Arduino Uno + 74HC00)
const int PIN_SBAR = 2;   // to 74HC00 pin 1
const int PIN_RBAR = 3;   // to 74HC00 pin 4
const int PIN_Q    = 4;   // from 74HC00 pin 3
const int PIN_QBAR = 5;   // from 74HC00 pin 6

void report(const char *event) {
    delay(5);
    Serial.print(event);
    Serial.print("  Q = ");
    Serial.print(digitalRead(PIN_Q));
    Serial.print("  Q' = ");
    Serial.println(digitalRead(PIN_QBAR));
}

void pulse_low(int pin) {          // a brief 0, then back to the resting 1
    digitalWrite(pin, LOW);
    delay(5);
    digitalWrite(pin, HIGH);
}

void setup(void) {
    Serial.begin(9600);
    pinMode(PIN_Q, INPUT);
    pinMode(PIN_QBAR, INPUT);
    report("power-up      ");      // read before touching the inputs
    digitalWrite(PIN_SBAR, HIGH);  // HIGH first, so that the pins
    digitalWrite(PIN_RBAR, HIGH);  // never drive a 0 by accident
    pinMode(PIN_SBAR, OUTPUT);     // now drive the resting 1: hold
    pinMode(PIN_RBAR, OUTPUT);
    pulse_low(PIN_SBAR);
    report("after set     ");
    report("still holding ");
    pulse_low(PIN_RBAR);
    report("after reset   ");
    report("still holding ");
}

void loop(void) {
}

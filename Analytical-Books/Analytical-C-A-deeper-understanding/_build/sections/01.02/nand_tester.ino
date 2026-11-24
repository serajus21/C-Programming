// nand_tester.ino  (Arduino Uno + 74HC00)
const int PIN_A = 2;   // to 74HC00 pin 1 (gate 1, input A)
const int PIN_B = 3;   // to 74HC00 pin 2 (gate 1, input B)
const int PIN_Y = 4;   // from 74HC00 pin 3 (gate 1, output)

void setup(void) {
    Serial.begin(9600);
    pinMode(PIN_A, OUTPUT);
    pinMode(PIN_B, OUTPUT);
    pinMode(PIN_Y, INPUT);
    Serial.println("A B | Y");
    for (int a = 0; a <= 1; ++a) {
        for (int b = 0; b <= 1; ++b) {
            digitalWrite(PIN_A, a);
            digitalWrite(PIN_B, b);
            delay(5);                  // let the output settle
            Serial.print(a);
            Serial.print(" ");
            Serial.print(b);
            Serial.print(" | ");
            Serial.println(digitalRead(PIN_Y));
        }
    }
}

void loop(void) {
}

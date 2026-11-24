// threshold.ino  (Arduino Uno)
void setup(void) {
    Serial.begin(9600);        // send text to the laptop at 9600 bits/s
    pinMode(2, INPUT);         // pin 2 is an input with no pull-up
}

void loop(void) {
    int raw = analogRead(A0);             // 0..1023 for 0 V..5 V
    float volts = raw * 5.0 / 1024.0;     // convert to volts
    int logic = digitalRead(2);           // how the chip reads it
    Serial.print(volts, 2);
    Serial.print(" V  ->  ");
    Serial.println(logic);
    delay(200);                           // five readings per second
}

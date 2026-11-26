// steps.ino  (Arduino Uno or ESP32)
// The Arduino version of Listing 02.01-5: one sketch, two machines.
void setup() {
  Serial.begin(115200);
  delay(500);
  int i[2];
  Serial.print("bytes in: char ");
  Serial.print((int)sizeof(char));
  Serial.print(", int ");
  Serial.print((int)sizeof(int));
  Serial.print(", long ");
  Serial.print((int)sizeof(long));
  Serial.print(", double ");
  Serial.print((int)sizeof(double));
  Serial.print(", pointer ");
  Serial.print((int)sizeof(&i[0]));
  Serial.println();
  Serial.print("p + 1 moves an int pointer by ");
  Serial.print((int)((char *)(&i[0] + 1) - (char *)&i[0]));
  Serial.print(" bytes");
  Serial.println();
}

void loop() {}

// boot_counter.ino  (Arduino Uno)
#include <EEPROM.h>

int ram_count = 0;                  // in SRAM: set to 0 at every start

void setup(void) {
    Serial.begin(9600);
    byte boots = EEPROM.read(0);    // in EEPROM: survives power-off
    boots = boots + 1;
    EEPROM.update(0, boots);        // writes only if the value changed
    ram_count = ram_count + 1;
    Serial.print("SRAM counter:   ");
    Serial.println(ram_count);
    Serial.print("EEPROM counter: ");
    Serial.println(boots);
}

void loop(void) {
}

run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
cd "$PWD/../_build/sections/03.01/fedora" || exit 1
for f in avr_hello avr_verbose; do run "avr-gcc -mmcu=atmega328p -std=c11 -Os -Wall -Wextra -pedantic $f.c -o $f.elf && avr-objcopy -O ihex -R .eeprom $f.elf $f.hex"; done
run "ls -l avr_hello.c avr_verbose.c avr_hello.elf avr_verbose.elf avr_hello.hex avr_verbose.hex; cmp avr_hello.hex avr_verbose.hex && echo HEX-IDENTICAL; avr-size avr_hello.elf avr_verbose.elf"
cd ../../03.02/fedora && rm -rf avr2 && mkdir avr2 && cd avr2 && cp ../avr_hello.c . 
run "avr-gcc -mmcu=atmega328p -std=c11 -Os -Wall -Wextra -pedantic -save-temps avr_hello.c -o avr_hello.elf && avr-objcopy -O ihex -R .eeprom avr_hello.elf avr_hello.hex && ls -l && file *"
run "head -1 avr_hello.hex; tail -1 avr_hello.hex"

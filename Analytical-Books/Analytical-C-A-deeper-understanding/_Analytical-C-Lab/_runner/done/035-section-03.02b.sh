F="$PWD/../_build/sections/03.02/fedora"; cd "$F" || exit 1
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
run "gcc -### -std=c23 hello.c -o hello 2>&1 | tail -4 | cut -c1-160"
run "ls avr_hello*"
run "avr-gcc -v -mmcu=atmega328p -std=c11 -Os avr_hello.c -o avr_hello.elf 2>&1 | grep -n -E 'cc1|/as|collect2' | cut -c1-120"
run "mkdir -p avr && cd avr && cp ../avr_hello.c . && avr-gcc -mmcu=atmega328p -std=c11 -Os -Wall -Wextra -pedantic -save-temps avr_hello.c -o avr_hello.elf && avr-objcopy -O ihex -R .eeprom avr_hello.elf avr_hello.hex && ls -l && file *"
run "gcc -save-temps -std=c23 hello.c -o prog && ls prog* hello.*"
run "rpm -q gcc binutils glibc"

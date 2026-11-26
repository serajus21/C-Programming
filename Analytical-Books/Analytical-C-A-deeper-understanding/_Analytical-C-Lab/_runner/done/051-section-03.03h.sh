F="$PWD/../_build/sections/03.03/fedora"; cd "$F" || exit 1
cp ../avr_blink.c ../semi.c ../self.h ../loop.c .
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
O="-std=c23 -Wall -Wextra -pedantic"
run "gcc $O semi.c -o semi"
run "gcc -std=c23 -E semi.c -o semi.i && grep -n 'hello, world' semi.i && gcc $O -c semi.i -o semi.o"
run "gcc -std=c23 -E -P semi.c -o flat.i && grep -n 'hello, world' flat.i && gcc $O -c flat.i -o flat.o"
run "grep -v pragma pragma.c > nopragma.c; gcc $O nopragma.c -o nopragma"
run "gcc $O -fsyntax-only loop.c 2>&1 | grep -c 'from self.h'; gcc $O -fsyntax-only loop.c 2>&1 | grep -E 'error|depth'"
run "gcc -std=c23 -E -dD hello.c | grep -c '^#define'"
A="avr-gcc -mmcu=atmega328p -std=c11 -Wall -Wextra -pedantic"
run "$A -Os -c avr_blink.c -o avr_blink.o && avr-nm avr_blink.o"
run "$A -Os avr_blink.c -o avr_blink.elf && avr-size avr_blink.elf"
run "$A -E -P avr_blink.c | grep -n -A3 '^_delay_ms\\|void _delay_ms' | head -12"
run "$A -E -P avr_blink.c | wc -l; $A -E -P avr_led.c | wc -l"
run "$A -O0 -c avr_blink.c -o b0.o"
run "$A -Os -S avr_blink.c -o - | sed -n '/^main:/,/rjmp/p'"

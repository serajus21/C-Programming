F="$PWD/../_build/sections/03.05/fedora"; cd "$F/y" || exit 1
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
run "avr-gcc -mmcu=atmega328p -std=c11 -Os -S avr_blink.c -o - | grep -v '^/\\*' | sed -n '/^main:/,/\\.size/p'"
run "printf 'here:\\n\\trjmp .\\n\\trjmp here\\n' | avr-as -mmcu=atmega328p -o dot.o && avr-objdump -dr dot.o | tail -6 && avr-nm -a dot.o | cat -A"

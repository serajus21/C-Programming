F="$PWD/../_build/sections/03.05/fedora"; cd "$F/y" || exit 1
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
run "avr-gcc -mmcu=atmega328p -std=c11 -Os -S avr_blink.c -o - | sed -n '/^main:/,/size/p'"
run "avr-objdump -dr avr_blink.o | sed -n '/<main>:/,\$p'"
run "avr-gcc -mmcu=atmega328p -std=c11 -Os avr_hello.c -o avr_hello.elf && avr-objdump -d avr_hello.elf | sed -n '/<__do_copy_data>:/,/<__bad_interrupt>/p'"
run "avr-objdump -s -j .data avr_hello.elf"
run "avr-size avr_hello.elf; avr-objdump -h avr_hello.elf | grep -A1 -E ' \\.(text|data|bss) '"
run "avr-ld --verbose -m avr5 | sed -n '/\\.data  *:/,/} *>data/p'"

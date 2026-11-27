F="$PWD/../_build/sections/03.06/fedora"; cd "$F" || exit 1
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
A="avr-gcc -mmcu=atmega328p -std=c11 -Os -Wall -Wextra -pedantic"
run "$A avr_hello.c -o avr_hello.elf -v 2>&1 | grep collect2 | tr ' ' '\n' | cat -n"
run "$A avr_hello.c -o avr_hello.elf -Wl,--trace"
run "$A avr_hello.c -o avr_hello.elf -Wl,-Map=avr_hello.map && grep -n -E '^\\.(text|data|bss)|^ \\.(vectors|init[0-9]|text|data|rodata|fini[0-9])|^ \\*\\(\\.init|crtatmega|_copy_data|_clear_bss|_exit|avr_hello' avr_hello.map | head -70"
run "file avr_hello.elf; avr-objdump -h avr_hello.elf"
run "avr-nm -n avr_hello.elf"
run "avr-objdump -d avr_hello.elf | sed -n '/<__vectors>:/,/<__ctors_end>/p' | head -12; avr-objdump -d avr_hello.elf | sed -n '/<__ctors_end>:/,/<__do_copy_data>/p'"
run "avr-objdump -d avr_hello.elf | sed -n '/<main>:/,\$p' | head -40"
run "avr-gcc -mmcu=atmega328p -std=c11 -Os -c avr_hello.c && avr-objdump -dr avr_hello.o | sed -n '/<main>:/,\$p' | head -30"
run "rpm -qf /usr/avr/lib/avr5/crtatmega328p.o 2>&1; ls /usr/avr/lib/avr5/ | head -30"
run "avr-nm /usr/avr/lib/avr5/crtatmega328p.o"

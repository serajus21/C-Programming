F="$PWD/../_build/sections/03.07/fedora"; cd "$F" || exit 1
tar xzf ../src2.tgz 2>/dev/null
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
G="gdb -batch -nx -ex 'set debuginfod enabled off'"
run "$G -ex 'break *0x401040' -ex run -ex 'info registers rip rsp rdx' -ex 'info symbol \$rdx' -ex 'x/gx 0x402fd8' -ex 'info symbol *(long *)0x402fd8' -ex 'x/3gx 0x402fe8' -ex 'info symbol *(long *)0x402ff8' -ex 'x/gx 0x403000' -ex 'x/4gx \$rsp' ./hello 2>&1 | grep -v -i debuginfod | grep -v -E '^ *<|^This GDB|^Enable|^To make'"
run "$G -ex 'break *0x40105f' -ex run -ex 'info registers rdi rsi rdx rcx r8 r9 rsp' -ex 'x/2gx \$rsp' ./hello 2>&1 | grep -v -i debuginfod | grep -v -E '^ *<|^This GDB|^Enable|^To make'"
run "strace -e trace=execve,write,exit_group ./hello"
A="avr-gcc -mmcu=atmega328p -std=c11 -Os -Wall -Wextra -pedantic"
run "$A avr_life.c -o avr_life.elf && avr-size avr_life.elf && avr-objdump -d avr_life.elf | sed -n '/<__ctors_end>:/,\$p'"
run "avr-nm -n avr_life.elf | grep -v -E ' N | a |Lname|Loc' | head -60"
run "$A avr_hello.c -o avr_hello.elf && avr-objdump -h avr_hello.elf | head -8"

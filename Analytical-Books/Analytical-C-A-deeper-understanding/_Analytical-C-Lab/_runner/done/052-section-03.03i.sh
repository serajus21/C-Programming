F="$PWD/../_build/sections/03.03/fedora"; cd "$F" || exit 1
A="avr-gcc -mmcu=atmega328p -std=c11 -Wall -Wextra -pedantic"
echo '$ '"$A -Os -S avr_blink.c -o - | sed -n '/^main:/,/size/p'"
$A -Os -S avr_blink.c -o - | sed -n '/^main:/,/\.size/p'
echo "[exit $?]"
echo; echo '$ '"$A -Os -E -P avr_blink.c | grep -n -A16 '^_delay_ms'"
$A -Os -E -P avr_blink.c | grep -n -A16 '^_delay_ms'
echo "[exit $?]"
echo; echo '$ '"$A -Os -E -P avr_blink.c | wc -l"; $A -Os -E -P avr_blink.c | wc -l
echo; echo '$ gcc -std=c23 -E -P hello.c | wc -l ; gcc -std=c23 -O2 -E -P hello.c | wc -l'; gcc -std=c23 -E -P hello.c | wc -l ; gcc -std=c23 -O2 -E -P hello.c | wc -l
echo; sed -n 100,115p /usr/avr/include/util/delay.h

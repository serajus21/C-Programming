F="$PWD/../_build/sections/03.03/fedora"; cd "$F/exp" || exit 1
printf '#include <stdio.h>\nint main(void) { return 0; }\n' > one.c
echo "== one vs three"; gcc -std=c23 -E one.c | wc -l; gcc -std=c23 -E three.c | wc -l; diff <(gcc -std=c23 -E one.c) <(gcc -std=c23 -E three.c)
echo "== stdio head"; sed -n 1,30p /usr/include/stdio.h | grep -v '^ *$' | grep -n -v '^   \|^/\*\|^ \*' ; grep -n '' /usr/include/stdio.h | sed -n 18,29p
cd ..
echo "== avr -Os lines 60-63"; avr-gcc -mmcu=atmega328p -std=c11 -Os -E -P avr_blink.c | sed -n 60,63p
echo "== sfr 168-173"; sed -n 168,173p /usr/avr/include/avr/sfr_defs.h
echo "== stdio 150-159"; grep -n '' /usr/include/stdio.h | sed -n 150,159p
echo "== -dD"; gcc -std=c23 -dD -E -P macros.c | grep -n 'SQUARE\|LIMIT' | head

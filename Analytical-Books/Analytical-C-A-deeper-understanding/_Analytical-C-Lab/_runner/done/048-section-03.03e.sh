F="$PWD/../_build/sections/03.03/fedora"; mkdir -p "$F/exp"; cd "$F/exp" || exit 1
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
O="-std=c23 -Wall -Wextra -pedantic"
printf '// semi.c\n// hello.c with one semicolon missing.\n#include <stdio.h>\n\nint main(void) {\n    printf("hello, world\\n")\n    return 0;\n}\n' > semi.c
run "cat -n semi.c"
run "gcc $O semi.c -o semi"
run "gcc -std=c23 -E semi.c -o semi.i; grep -n 'hello, world' semi.i; gcc $O -c semi.i -o semi.o"
run "gcc -std=c23 -E -P semi.c -o flat.i; grep -n 'hello, world' flat.i; gcc $O -c flat.i -o flat.o"
run "gcc -std=c23 -v -E - </dev/null 2>&1 | sed -n '/search starts here/,/End of search/p'"
run "gcc -std=c23 -I. -v -E - </dev/null 2>&1 | sed -n '/search starts here/,/End of search/p'"
run "cat /usr/include/stdc-predef.h | grep -v '^ *\$' | grep -v '^/\\*\\|^ *\\*\\|^   ' | head -30"
run "grep -n -E '^# *define' /usr/include/stdc-predef.h"
run "gcc -std=c23 -ffreestanding -E -P ../hello.c | wc -l; gcc -std=c23 -ffreestanding -E ../hello.c | grep -c stdc-predef"
run "grep -n -B2 -A2 'bits/stdio.h' /usr/include/stdio.h"
run "grep -n -B3 -A1 'define __USE_EXTERN_INLINES' /usr/include/features.h"
run "gcc $O -O2 -c ../hello.c -o h2.o && nm h2.o; gcc $O -O2 -c ../root.c -o r2.o && nm r2.o"
run "gcc -H -fsyntax-only -std=c23 ../hello.c 2>&1 | grep '^\\.' | wc -l; gcc -H -fsyntax-only -std=c23 ../hello.c 2>&1 | grep '^\\.' | sed 's/^\\.* //' | sort -u | wc -l; gcc -H -fsyntax-only -std=c23 ../hello.c 2>&1 | grep -c stdc-predef"
printf 'int counter = 0;\n' > def.h
printf '#include "def.h"\nint main(void) { return counter; }\n' > a.c
printf '#include "def.h"\nint other(void) { return counter + 1; }\n' > b.c
run "gcc $O a.c b.c -o ab"
printf '#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n#include <math.h>\n#include <stdint.h>\n#include <stdbool.h>\n#include <time.h>\n#include <errno.h>\n#include <ctype.h>\n#include <limits.h>\nint main(void) { return 0; }\n' > ten.c
run "wc -l ten.c; gcc -std=c23 -E ten.c | wc -l; gcc -std=c23 -E -P ten.c | wc -l"
run "printf '#include <stdio.h>\n#include <stdio.h>\n#include <stdio.h>\nint main(void) { return 0; }\n' > three.c; gcc -std=c23 -E three.c | wc -l; gcc -std=c23 -E ../hello.c | wc -l"
cd ..
run "avr-gcc -mmcu=atmega328p -std=c11 -Os -c avr_led.c -o avr_led.o && avr-nm avr_led.o"
run "sed -n 120,182p /usr/avr/include/avr/sfr_defs.h"
run "sed -n 140,152p /usr/avr/include/avr/portpins.h"
run "grep -n -E 'static __inline__|^_delay_ms|^_delay_us|__builtin_avr_delay_cycles' /usr/avr/include/util/delay.h | head"
run "grep -n -E 'define (DDRB|PORTB|PINB) ' /usr/avr/include/avr/iom328p.h"

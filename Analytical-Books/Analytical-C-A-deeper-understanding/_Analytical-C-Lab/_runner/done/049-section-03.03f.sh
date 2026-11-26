cd "$PWD/../_build/sections/03.03/fedora" || exit 1
sed -n 140,160p /usr/avr/include/util/delay.h
echo ==; grep -n '_delay_ms\|_delay_us\|__inline\|static' /usr/avr/include/util/delay.h | head -20
echo ==; sed -n 100,112p /usr/include/stdio.h; sed -n 150,160p /usr/include/stdio.h
echo ==; gcc -std=c23 -E hello.c | grep -n 'puts\b' | head

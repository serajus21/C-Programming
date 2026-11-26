cd "$PWD/../_build/sections/03.03/fedora" || exit 1
sed -n 1,35p /usr/include/stdc-predef.h | grep -n -i 'implicit\|preinclude\|knows'
echo ==; gcc -std=c23 -ffreestanding -E hello.c | head -8
echo ==; printf 'int x;\n' | gcc -std=c23 -nostdinc -E - | head -5
echo ==; gcc -std=c23 -E -dI hello.c | sed -n 1,12p

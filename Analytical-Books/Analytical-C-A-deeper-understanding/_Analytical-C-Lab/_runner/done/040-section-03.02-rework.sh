F="$PWD/../_build/sections/03.02/fedora"; mkdir -p "$F/rw"; cd "$F/rw" || exit 1
cp ../hello.c ../greet.c ../escape.c ../../avr_hello.c . 2>/dev/null
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
O="-std=c23 -Wall -Wextra -pedantic"
run "gcc $O -c greet.c && objdump -dr greet.o"
printf 'int f(int n){ int s = 0; for (int i = 0; i < n; ++i) s += i; return s; }\n' > loop.c
run "cat loop.c; gcc -std=c23 -S loop.c -o - | grep -E 'jmp|jl|jle|jg|\.L[0-9]+:'"
run "gcc -std=c23 -c loop.c && objdump -d loop.o | grep -E 'jmp|jl|jle|jg'; objdump -r loop.o"
run "gcc -dumpspecs | grep -A1 '^\*startfile:' | cut -c1-400"
run "avr-gcc -v -mmcu=atmega328p -c avr_hello.c -o /dev/null 2>&1 | grep -i 'specs'"
run "grep -A1 -E '^\*(cpp|asm_arch):' \"\$(avr-gcc -print-file-name=device-specs/specs-atmega328p)\""
run "gcc -pipe -v -std=c23 hello.c -o hp 2>&1 | grep -E '^ as '"
run "gcc -no-integrated-cpp -v -std=c23 hello.c -o hn 2>&1 | grep -E '/cc1 | as |/collect2 ' | cut -c1-110"
run "gcc -Wl,-v -std=c23 hello.c -o hv 2>&1 | head -3 | cut -c1-200"
printf '#define CAT(a,b) a/**/b\nint CAT(foo,bar) = 1;\n' > old.c
run "cat old.c; gcc -E -P old.c; gcc -E -P -traditional-cpp old.c | grep -v '^\$'"
printf '#define abc + 1\nint x = 12abc;\nint y = 12 abc;\n' > mac.c
run "cat mac.c; gcc -std=c23 -E -P mac.c; gcc -std=c23 -c mac.c"
printf 'int main(void){ int a = 1 @ 2; return a; }\n' > at.c
run "cat at.c; gcc -std=c23 at.c -o at"
printf '#define int long\nint main(void){ int x = sizeof(int); return x; }\n' > kw.c
run "cat kw.c; gcc $O kw.c -o kw && ./kw; echo \$?"
printf 'int main(void){ return (unsigned char)\"A\"[0]; }\n' > ebc.c
run "cat ebc.c; gcc -std=c23 ebc.c -o ebc && ./ebc; echo \$?; gcc -std=c23 -fexec-charset=IBM1047 ebc.c -o ebc2 && ./ebc2; echo \$?"
printf 'int main(void){ return (unsigned char)\"\\\\n\"[0]; }\n' > nl.c
run "cat nl.c; gcc -std=c23 -fexec-charset=IBM1047 nl.c -o nl && ./nl; echo \$?"
printf 'int main(void){ return (unsigned char)\"\\\\x41\"[0]; }\n' > hx.c
run "cat hx.c; gcc -std=c23 -fexec-charset=IBM1047 hx.c -o hx && ./hx; echo \$?"
run "gcc -std=c23 -fdump-tree-original -c hello.c -o /dev/null; ls hello.c.*original*; cat hello.c.*.original"
run "clang -### -fno-integrated-as -std=c23 hello.c -o hc 2>&1 | grep -E '^ \"' | cut -c1-80"
printf '#define X 1 \\ \n+1\nint main(void){ return X; }\n' > bsp.c
run "cat -A bsp.c; gcc -std=c23 -Wall bsp.c -o bsp; ./bsp; echo \$?"
for v in 12abc 0b2 0xE+1 1.2.3.4 0xF+1; do printf "int x = $v;\n" > q.c; run "cat q.c; gcc -std=c23 -c q.c -o q.o && echo compiled"; done
run "printf 'int x = 0xF+1;\nint main(void){ return x; }\n' > q2.c; gcc -std=c23 q2.c -o q2 && ./q2; echo \$?"
run "gcc -std=c23 -S escape.c -o - | grep -E 'call'"
run "gcc -std=c23 -E escape.c | grep -c '' ; gcc -std=c23 -g -c greet.c -o greetg.o && gcc greetg.o -o greetg"
run "rpm -q glibc-gconv-extra 2>&1"

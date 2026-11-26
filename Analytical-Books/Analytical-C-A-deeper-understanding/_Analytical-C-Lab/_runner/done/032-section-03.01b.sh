# Job 03.01b: further checks for §03.01 on the reader's Fedora.
set -u
F="$PWD/../_build/sections/03.01/fedora"; cd "$F" || exit 1
cp ../squashed.c .
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
O="-std=c23 -Wall -Wextra -pedantic"
run "cat /etc/fedora-release; uname -r"
run "gcc -v 2>&1 | grep -o -- '--enable-default-pie' || echo no-default-pie; file hello"
run "gcc $O -S squashed.c -o squashed.s; diff hello.s squashed.s"
run "gcc -std=c23 -H -fsyntax-only hello.c 2>&1 | wc -l; gcc -std=c23 -H -fsyntax-only hello.c 2>&1 | grep -c '^\.'; gcc -std=c23 -H -fsyntax-only hello.c 2>&1 | sed -n '30,60p'"
run "script -q -c 'strace -e trace=write ./hello' /dev/null | cat -A | head"
run "objdump -s -j .rodata hello"
run "readelf -S -W hello | sed -n '1,60p'"
run "python3 -c \"import re;d=open('hello','rb').read();print(len(d), sum(len(m.group()) for m in re.finditer(rb'\\\\x00{64,}', d)))\""
run "ls -lL /lib64/libc.so.6"
run "./retn > /dev/full; echo \$?"
run "strace -o full.trace -e trace=write,exit_group ./retn > /dev/full; cat full.trace"
run "printf '#include <stdio.h>\nint main(void){ int n=printf(\"hello, world\\\\n\"); int a=ferror(stdout); int f=fflush(stdout); int b=ferror(stdout); fprintf(stderr,\"n=%%d ferror-before=%%d fflush=%%d ferror-after=%%d\\\\n\",n,a,f,b); return 0; }\n' > ferr.c; gcc $O ferr.c -o ferr && ./ferr > /dev/full"
run "nm count | grep -E ' U '"
run "gcc $O -c layout.c -o layout.o && cmp hello.o layout.o; objcopy -O binary -j .text layout.o lay.bin && cmp main.bin lay.bin && echo text-identical"
run "./status 512; echo \$?"
run "sed 's/        printf(\"first check failed\\\\n\");/        { printf(\"first check failed\\\\n\");/; s/        return 1;/        return 1; }/' indent.c > indent2.c; sed -n 6,9p indent2.c; gcc $O indent2.c -o indent2 && ./indent2; echo \$?"
run "cmp avr_hello.elf avr_verbose.elf; avr-readelf -s avr_hello.elf | grep FILE; avr-nm avr_hello.elf | grep -i -E ' (main|send)'"
run "avr-objdump -d avr_hello.elf | sed -n '/<main>:/,\$p' | head -30"
run "dnf list --installed 2>/dev/null | grep -i -E '^(simavr|glibc-static|avr-gcc|avr-libc|clang)\\.' ; dnf info simavr 2>&1 | head -3"

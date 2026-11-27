F="$PWD/../_build/sections/03.07/fedora"; cd "$F" || exit 1
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
G="gdb -batch -nx -ex 'set debuginfod enabled off'"
run "nm hello | grep -w -E 'main|_start'; cmp hello ../../03.06/fedora/hello && echo same-as-03.06"
run "$G -ex starti -ex 'info registers rip rsp rdx' -ex 'info symbol \$pc' -ex 'x/gx 0x403000' -ex 'x/gx 0x402fd8' -ex 'x/3gx 0x402fe8' -ex 'x/6gx \$rsp' -ex 'info proc mappings' ./hello"
run "$G -ex 'break _start' -ex run -ex 'info registers rip rsp rdx' -ex 'info symbol \$rdx' -ex 'x/gx 0x403000' -ex 'x/gx 0x402fd8' -ex 'info symbol *(long *)0x402fd8' -ex 'x/3gx 0x402fe8' -ex 'info symbol *(long *)0x402ff8' -ex 'x/4gx \$rsp' -ex 'x/s *(char **)(\$rsp+8)' ./hello"
run "$G -ex 'break main' -ex run -ex bt -ex 'x/gx 0x403000' -ex 'info proc mappings' -ex 'break *0x401144' -ex continue -ex 'x/gx 0x403000' -ex 'info symbol *(long *)0x403000' -ex 'p (void *)puts' ./hello"
run "$G -ex 'break before' -ex run -ex bt -ex 'break bye' -ex continue -ex bt -ex 'break after' -ex continue -ex bt ./order"
run "$G -ex 'break main' -ex run -ex 'info registers rdi rsi rdx' -ex 'x/s *(char **)\$rsi' ./hello"

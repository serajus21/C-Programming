F="$PWD/../_build/sections/03.07/fedora"; mkdir -p "$F"; cd "$F" || exit 1
tar xzf ../src.tgz 2>/dev/null
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
O="-std=c23 -Wall -Wextra -pedantic"
for f in hello stack order clock where cet; do gcc $O $f.c -o $f; done
run "./hello; strace ./hello"
run "LD_SHOW_AUXV=1 ./hello"
run "./stack; ./stack one two"
run "./where; ./where; setarch -R ./where"
run "gcc $O -fPIE -pie where.c -o where_pie && ./where_pie && ./where_pie && setarch -R ./where_pie && readelf -h where_pie | grep -E 'Type|Entry'"
run "./order"
run "./clock; strace -c ./clock 2>&1 >/dev/null | tail -25"
run "./cet; gcc $O -fcf-protection=full cet.c -o cet_cf && ./cet_cf && readelf -n cet_cf | grep -A1 -i 'x86 feature'; readelf -n hello | grep -A1 -i 'x86 feature'; readelf -n /usr/bin/ls | grep -A1 -i 'x86 feature'; GLIBC_TUNABLES=glibc.cpu.x86_shstk=on ./cet_cf; GLIBC_TUNABLES=glibc.cpu.x86_shstk=on ./cet"
run "LD_DEBUG=libs ./hello 2>&1"
run "LD_DEBUG=bindings ./hello 2>&1"
run "LD_BIND_NOW=1 LD_DEBUG=bindings ./hello 2>&1"
run "LD_DEBUG=statistics ./hello 2>&1"
run "cat /proc/sys/kernel/randomize_va_space; getconf PAGESIZE"

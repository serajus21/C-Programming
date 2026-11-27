F="$PWD/../_build/sections/04.01/fedora"; cd "$F" || exit 1
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
O="-fno-asynchronous-unwind-tables -fcf-protection=none -fno-stack-protector -U_FORTIFY_SOURCE"
run "sed 's/10;/2;/' div10.c > div2.c; gcc -std=c23 -O2 -S $O div2.c -o - | grep -A3 '^tenth:'"
run "gcc -std=c23 -O2 -S $O div16.c -o - | grep -A3 '^tenth:'"
cat > zero.c <<'Z'
#include <stdio.h>
int main(void) {
    printf("[%#x] [%#o] [%#b] [%#x] [%#B]\n", 0u, 0u, 0u, 255u, 5u);
    printf("%s %s\n", _Generic(3735928559, int: "int", long: "long", unsigned: "unsigned", default: "other"),
                      _Generic(0xDEADBEEF, int: "int", long: "long", unsigned: "unsigned", default: "other"));
}
Z
run "gcc -std=c23 -Wall -Wextra -pedantic zero.c -o zero && ./zero"
run "cp same perm_demo && chmod 640 perm_demo && stat -c '%a %A' perm_demo && chmod 755 perm_demo && stat -c '%a %A' perm_demo"
run "for n in 255 256 65535 65536; do printf '%d: %o %x\n' \$n \$n \$n; done"
run "ls -l /usr/bin/passwd | cut -c1-10; stat -c '%a %A' /usr/bin/passwd /tmp"
run "getconf PAGESIZE; printf '%x\n' \$(getconf PAGESIZE)"

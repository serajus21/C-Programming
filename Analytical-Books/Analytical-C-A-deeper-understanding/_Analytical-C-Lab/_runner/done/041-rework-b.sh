F="$PWD/../_build/sections/03.02/fedora/rw"; cd "$F" || exit 1
run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
cat > nl.c <<'EOF'
int main(void){ return (unsigned char)"\n"[0]; }
EOF
cat > hx.c <<'EOF'
int main(void){ return (unsigned char)"\x41"[0]; }
EOF
run "cat nl.c; gcc -std=c23 nl.c -o nl0 && ./nl0; echo \$?; gcc -std=c23 -fexec-charset=IBM1047 nl.c -o nl && ./nl; echo \$?"
run "cat hx.c; gcc -std=c23 -fexec-charset=IBM1047 hx.c -o hx && ./hx; echo \$?"
run "grep -A1 -E '^\*(cpp_mcu|cpp_rodata_in_ram|cpp_avrlibc):' \"\$(avr-gcc -print-file-name=device-specs/specs-atmega328p)\""
run "gcc -dumpspecs | grep -c 'enable-default-pie'; gcc -Q --help=common | grep -E '^ +-f(PIE|pie) '"

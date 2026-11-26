# Probe: what the reader's Fedora toolchain is.
echo "== pwd"; pwd
echo "== locale"; locale 2>&1 | head -3; echo "LANG=$LANG"
echo "== gcc"; gcc --version | head -1; gcc -dumpmachine; gcc -dumpversion
echo "== default PIE?"; gcc -v 2>&1 | tr ' ' '\n' | grep -E 'enable-default-pie|enable-host-pie' ; gcc -Q --help=common 2>/dev/null | grep -E '^\s+-f(PIE|pie|PIC|pic)\s'
echo "== gcc -print-prog-name"; for p in cc1 as collect2 ld; do printf '%s -> %s\n' $p "$(gcc -print-prog-name=$p)"; done
echo "== crt files"; for f in crt1.o Scrt1.o crti.o crtn.o crtbegin.o crtbeginS.o crtend.o crtendS.o libc.a libc.so; do printf '%s -> %s\n' $f "$(gcc -print-file-name=$f)"; done
echo "== binutils"; ld --version | head -1; as --version | head -1; readelf --version | head -1
echo "== glibc"; ldd --version | head -1
echo "== avr"; avr-gcc --version 2>&1 | head -1; avr-objdump --version 2>&1 | head -1; ls /usr/avr/include/avr/version.h 2>&1 && grep -m1 '__AVR_LIBC_VERSION_STRING__' /usr/avr/include/avr/version.h
echo "== simavr"; which simavr 2>&1; simavr --help 2>&1 | head -2
echo "== others"; for t in gdb strace ltrace file eu-readelf clang node; do printf '%s: ' $t; command -v $t || echo missing; done
echo "== uname"; uname -srm

run() { printf '\n$ %s\n' "$*"; bash -c "$*" 2>&1; printf '[exit %s]\n' "$?"; }
run "which strace gdb ltrace setarch; uname -r; cat /proc/sys/kernel/randomize_va_space"
run "grep -o -w -E 'user_shstk|ibt|shstk' /proc/cpuinfo | sort | uniq -c"
run "grep -E 'x86_Thread|Speculation' /proc/self/status"
run "cat /etc/ld.so.conf; ls /etc/ld.so.conf.d | head; ldconfig -p | grep -E 'libc.so.6|libm.so.6'"

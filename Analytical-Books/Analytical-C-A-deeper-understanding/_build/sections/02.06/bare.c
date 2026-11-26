// bare.c
// A Linux program with no C library: no main, no printf, no exit.
static long sys_write(long fd, const void *buf, unsigned long n) {
    long ret;
    __asm__ volatile ("syscall"                 // ask the kernel directly
                      : "=a"(ret)
                      : "a"(1L), "D"(fd), "S"(buf), "d"(n)  // 1 = write
                      : "rcx", "r11", "memory");
    return ret;
}

[[noreturn]] static void sys_exit(long code) {
    __asm__ volatile ("syscall" : : "a"(60L), "D"(code));   // 60 = exit
    __builtin_unreachable();
}

void _start(void) {                             // where the kernel jumps
    static const char msg[] = "hello, with no C library\n";
    sys_write(1, msg, sizeof msg - 1);          // 1 = standard output
    sys_exit(0);
}

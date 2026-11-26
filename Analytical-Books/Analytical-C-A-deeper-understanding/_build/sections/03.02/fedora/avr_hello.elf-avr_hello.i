# 0 "avr_hello.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "avr_hello.c"



# 1 "/usr/avr/include/avr/io.h" 1 3
# 99 "/usr/avr/include/avr/io.h" 3
# 1 "/usr/avr/include/avr/sfr_defs.h" 1 3
# 126 "/usr/avr/include/avr/sfr_defs.h" 3
# 1 "/usr/avr/include/inttypes.h" 1 3
# 37 "/usr/avr/include/inttypes.h" 3
# 1 "/usr/lib/gcc/avr/15.3.0/include/stdint.h" 1 3 4
# 9 "/usr/lib/gcc/avr/15.3.0/include/stdint.h" 3 4
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
# 1 "/usr/avr/include/stdint.h" 1 3 4
# 125 "/usr/avr/include/stdint.h" 3 4
typedef signed int int8_t __attribute__((__mode__(__QI__)));
typedef unsigned int uint8_t __attribute__((__mode__(__QI__)));
typedef signed int int16_t __attribute__ ((__mode__ (__HI__)));
typedef unsigned int uint16_t __attribute__ ((__mode__ (__HI__)));
typedef signed int int32_t __attribute__ ((__mode__ (__SI__)));
typedef unsigned int uint32_t __attribute__ ((__mode__ (__SI__)));

typedef signed int int64_t __attribute__((__mode__(__DI__)));
typedef unsigned int uint64_t __attribute__((__mode__(__DI__)));
# 146 "/usr/avr/include/stdint.h" 3 4
typedef int16_t intptr_t;




typedef uint16_t uintptr_t;
# 163 "/usr/avr/include/stdint.h" 3 4
typedef int8_t int_least8_t;




typedef uint8_t uint_least8_t;




typedef int16_t int_least16_t;




typedef uint16_t uint_least16_t;




typedef int32_t int_least32_t;




typedef uint32_t uint_least32_t;







typedef int64_t int_least64_t;






typedef uint64_t uint_least64_t;
# 217 "/usr/avr/include/stdint.h" 3 4
typedef int8_t int_fast8_t;




typedef uint8_t uint_fast8_t;




typedef int16_t int_fast16_t;




typedef uint16_t uint_fast16_t;




typedef int32_t int_fast32_t;




typedef uint32_t uint_fast32_t;







typedef int64_t int_fast64_t;






typedef uint64_t uint_fast64_t;
# 277 "/usr/avr/include/stdint.h" 3 4
typedef int64_t intmax_t;




typedef uint64_t uintmax_t;
# 12 "/usr/lib/gcc/avr/15.3.0/include/stdint.h" 2 3 4
#pragma GCC diagnostic pop
# 38 "/usr/avr/include/inttypes.h" 2 3
# 77 "/usr/avr/include/inttypes.h" 3
typedef int32_t int_farptr_t;





typedef uint32_t uint_farptr_t;
# 127 "/usr/avr/include/avr/sfr_defs.h" 2 3
# 100 "/usr/avr/include/avr/io.h" 2 3
# 254 "/usr/avr/include/avr/io.h" 3
# 1 "/usr/avr/include/avr/iom328p.h" 1 3
# 255 "/usr/avr/include/avr/io.h" 2 3
# 785 "/usr/avr/include/avr/io.h" 3
# 1 "/usr/avr/include/avr/portpins.h" 1 3
# 786 "/usr/avr/include/avr/io.h" 2 3

# 1 "/usr/avr/include/avr/common.h" 1 3
# 788 "/usr/avr/include/avr/io.h" 2 3

# 1 "/usr/avr/include/avr/version.h" 1 3
# 790 "/usr/avr/include/avr/io.h" 2 3






# 1 "/usr/avr/include/avr/fuse.h" 1 3
# 239 "/usr/avr/include/avr/fuse.h" 3
typedef struct
{
    unsigned char low;
    unsigned char high;
    unsigned char extended;
} __fuse_t;
# 797 "/usr/avr/include/avr/io.h" 2 3


# 1 "/usr/avr/include/avr/lock.h" 1 3
# 800 "/usr/avr/include/avr/io.h" 2 3
# 5 "avr_hello.c" 2


# 6 "avr_hello.c"
static void send(char c) {
    while (!(
# 7 "avr_hello.c" 3
            (*(volatile uint8_t *)(0xC0)) 
# 7 "avr_hello.c"
                   & (1 << 
# 7 "avr_hello.c" 3
                           5
# 7 "avr_hello.c"
                                ))) { }
    
# 8 "avr_hello.c" 3
   (*(volatile uint8_t *)(0xC6)) 
# 8 "avr_hello.c"
        = c;
}

int main(void) {
    
# 12 "avr_hello.c" 3
   (*(volatile uint8_t *)(0xC0)) 
# 12 "avr_hello.c"
          = (1 << 
# 12 "avr_hello.c" 3
                  1
# 12 "avr_hello.c"
                      );
    
# 13 "avr_hello.c" 3
   (*(volatile uint16_t *)(0xC4)) 
# 13 "avr_hello.c"
         = 16;
    
# 14 "avr_hello.c" 3
   (*(volatile uint8_t *)(0xC1)) 
# 14 "avr_hello.c"
          = (1 << 
# 14 "avr_hello.c" 3
                  3
# 14 "avr_hello.c"
                       );
    for (const char *p = "hello, world\r\n"; *p != '\0'; ++p) {
        send(*p);
    }
    for (;;) { }
}

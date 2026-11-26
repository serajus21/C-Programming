// wordmem.c
// A model of a word-addressed memory like the PDP-7's, on which B was born:
// 18-bit words, and strings packed two 9-bit characters to a word.
#include <stdio.h>
#include <stdint.h>

#define WORD_MASK 0777777u          // eighteen 1 bits, written in octal
#define EOT       04u               // B's end-of-string character, '*e'

uint32_t mem[32];                   // each element models one 18-bit word

// B's char(s, n): character n of the string that begins at word s.
unsigned b_char(unsigned s, unsigned n) {
    uint32_t word = mem[s + n / 2];         // which word holds it?
    unsigned shift = (n % 2 == 0) ? 9 : 0;  // which half of that word?
    return (word >> shift) & 0777u;         // cut out its 9 bits
}

// B's lchar(s, n, c): replace character n, leaving its neighbor alone.
void b_lchar(unsigned s, unsigned n, unsigned c) {
    uint32_t *word = &mem[s + n / 2];
    unsigned shift = (n % 2 == 0) ? 9 : 0;
    uint32_t keep = *word & ~(0777u << shift) & WORD_MASK;
    *word = keep | ((c & 0777u) << shift);  // read, modify, write back
}

// Lay out a string at word s, as B laid out a string constant.
void pack(unsigned s, const char *text) {
    unsigned n = 0;
    while (text[n] != '\0') {
        b_lchar(s, n, (unsigned char)text[n]);
        ++n;
    }
    b_lchar(s, n, EOT);
}

// Listing 02.01-1, translated into C: the length of a string.
unsigned b_length(unsigned s) {
    unsigned n = 0;
    while (b_char(s, n) != EOT) {
        ++n;
    }
    return n;
}

void show(unsigned s, unsigned words) {
    for (unsigned w = s; w < s + words; ++w) {
        printf("  word %2u: %06o\n", w, (unsigned)mem[w]);
    }
}

int main(void) {
    pack(10, "hello, world");
    printf("The string, as 18-bit words in octal:\n");
    show(10, 7);
    printf("length = %u\n", b_length(10));

    b_lchar(10, 7, 'W');                    // character 7 is the 'w'
    printf("After replacing character 7:\n");
    show(13, 1);
    printf("The string now reads: ");
    for (unsigned n = 0; b_char(10, n) != EOT; ++n) {
        putchar((int)b_char(10, n));
    }
    putchar('\n');
}

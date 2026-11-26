// secret.c
// Wiping a password from memory before returning.
#include <string.h>

void read_password(char *buf, size_t size);     // defined elsewhere
void check_password(const char *buf);           // defined elsewhere

void login(void) {
    char secret[64];
    read_password(secret, sizeof secret);
    check_password(secret);
    memset(secret, 0, sizeof secret);           // wipe it before returning
}

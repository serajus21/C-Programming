#define _GNU_SOURCE
#include "header.h"
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/uio.h>
#include <time.h>
#include <unistd.h>

/* Ask Linux to copy bytes from the other process into our own int. */
int read_remote_int(pid_t process, uintptr_t address, int *value)
{
    struct iovec local = {value, sizeof(*value)};
    struct iovec remote = {(void *)address, sizeof(*value)};
    ssize_t count = process_vm_readv(process, &local, 1, &remote, 1, 0);
    if (count == (ssize_t)sizeof(*value)) return 0;
    if (count >= 0) errno = EIO;
    return -1;
}

static uintmax_t parse_number(const char *text, int base, uintmax_t maximum)
{
    char *end;
    errno = 0;
    uintmax_t value = strtoumax(text, &end, base);
    if (text[0] == '-' || end == text || *end != '\0' || errno ||
        value == 0 || value > maximum) {
        fprintf(stderr, "Invalid process ID or address: %s\n", text);
        exit(EXIT_FAILURE);
    }
    return value;
}

int main(int argc, char **argv)
{
    if (argc != 4) {
        fprintf(stderr, "Usage: %s PID FIRST_ADDRESS SECOND_ADDRESS\n"
                        "Run ./add and copy the command it prints.\n", argv[0]);
        return EXIT_FAILURE;
    }
    pid_t process = (pid_t)parse_number(argv[1], 10, INT_MAX);
    uintptr_t a = (uintptr_t)parse_number(argv[2], 16, UINTPTR_MAX);
    uintptr_t b = (uintptr_t)parse_number(argv[3], 16, UINTPTR_MAX);
    const struct timespec delay = {0, 200000000};
    puts("Reading every 0.2 seconds. Ctrl+C stops the inspector.");
    puts("Process virtual addresses; the two reads are separate snapshots.");
    printf("%-14s %-20s %-14s %s\n", "Variable name", "Memory address",
           "Size (bytes)", "Value");
    puts("-------------- -------------------- -------------- ------------");
    int rows_printed = 0;
    int interactive = isatty(STDOUT_FILENO);
    for (;;) {
        int first, second;
        if (read_remote_int(process, a, &first) ||
            read_remote_int(process, b, &second)) {
            if (errno == ESRCH) {
                puts("\nThe addition process has exited.");
                return EXIT_SUCCESS;
            }
            perror("\nCannot read the addition process");
            fputs("Use the same Linux user. The target must still be running, "
                  "and Linux must permit process inspection.\n", stderr);
            return EXIT_FAILURE;
        }
        /* Move back to the first data row to refresh the table in place. */
        if (interactive && rows_printed) {
            printf("\033[2A");
        }
        const char *clear_line = interactive ? "\033[2K\r" : "";
        printf("%s%-14s 0x%-18" PRIxPTR " %-14zu %d\n",
               clear_line, "first", a, sizeof(first), first);
        printf("%s%-14s 0x%-18" PRIxPTR " %-14zu %d\n",
               clear_line, "second", b, sizeof(second), second);
        rows_printed = 1;
        fflush(stdout);
        nanosleep(&delay, NULL);
    }
}

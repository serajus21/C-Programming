#ifndef MEMORY_INSPECT_HEADER_H
#define MEMORY_INSPECT_HEADER_H
#include <stdint.h>
#include <sys/types.h>
int read_remote_int(pid_t process, uintptr_t address, int *value);
#endif

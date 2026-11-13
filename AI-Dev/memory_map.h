#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H

#include <stddef.h>

typedef enum {
    MEMORY_INT,
    MEMORY_LONG_LONG,
    MEMORY_DOUBLE,
    MEMORY_OPERATION,
    MEMORY_LONG_LONG_POINTER,
    MEMORY_DOUBLE_POINTER
} MemoryKind;

typedef struct {
    const char *name;
    const char *type;
    const void *address;
    size_t size;
    MemoryKind kind;
} MemoryEntry;

void memory_map_show(const char *scope, const MemoryEntry *entries, size_t count);

#define MEMORY_ENTRY(variable, type_name, value_kind) \
    { #variable, type_name, &(variable), sizeof(variable), value_kind }

#endif

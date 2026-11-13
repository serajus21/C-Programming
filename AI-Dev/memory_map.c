#include "memory_map.h"
#include "headers.h"
#include <stdio.h>
#include <unistd.h>

void memory_map_show(const char *scope, const MemoryEntry *entries, size_t count)
{
    printf("\nMemory map: %s (PID %ld)\n", scope, (long)getpid());
    printf("%-20s %-18s %-18s %-18s %s\n",
           "Variable", "Type", "Address", "Value", "Bytes");
    for (size_t i = 0; i < count; ++i) {
        const MemoryEntry *entry = &entries[i];
        char value[64];
        switch (entry->kind) {
        case MEMORY_INT:
            snprintf(value, sizeof(value), "%d", *(const int *)entry->address);
            break;
        case MEMORY_LONG_LONG:
            snprintf(value, sizeof(value), "%lld", *(const long long *)entry->address);
            break;
        case MEMORY_DOUBLE:
            snprintf(value, sizeof(value), "%.10g", *(const double *)entry->address);
            break;
        case MEMORY_OPERATION:
            snprintf(value, sizeof(value), "%d", *(const Operation *)entry->address);
            break;
        case MEMORY_LONG_LONG_POINTER:
            snprintf(value, sizeof(value), "%p",
                     (void *)*(long long *const *)entry->address);
            break;
        case MEMORY_DOUBLE_POINTER:
            snprintf(value, sizeof(value), "%p",
                     (void *)*(double *const *)entry->address);
            break;
        default:
            snprintf(value, sizeof(value), "unknown");
        }
        printf("%-20s %-18s %-18p %-18s %zu\n", entry->name,
               entry->type, entry->address, value, entry->size);
    }
    putchar('\n');
}

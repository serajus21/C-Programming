#include "headers.h"
#include <limits.h>
#include "memory_map.h"

int calculate(Operation operation, long long left, long long right,
              long long *integer_result, double *division_result)
{
    const MemoryEntry parameter_entries[] = {
        MEMORY_ENTRY(operation, "Operation", MEMORY_OPERATION),
        MEMORY_ENTRY(left, "long long", MEMORY_LONG_LONG),
        MEMORY_ENTRY(right, "long long", MEMORY_LONG_LONG),
        MEMORY_ENTRY(integer_result, "long long *", MEMORY_LONG_LONG_POINTER),
        MEMORY_ENTRY(division_result, "double *", MEMORY_DOUBLE_POINTER)
    };
    memory_map_show("calculate (parameters)", parameter_entries,
                    sizeof(parameter_entries) / sizeof(parameter_entries[0]));

    switch (operation) {
    case OP_SUM:
        return __builtin_add_overflow(left, right, integer_result) ? 2 : 0;
    case OP_SUBTRACT:
        return __builtin_sub_overflow(left, right, integer_result) ? 2 : 0;
    case OP_MULTIPLY:
        return __builtin_mul_overflow(left, right, integer_result) ? 2 : 0;
    case OP_DIVIDE:
        if (right == 0) return 1;
        *division_result = (double)left / (double)right;
        return 0;
    case OP_REMAINDER:
        if (right == 0) return 1;
        if (left == LLONG_MIN && right == -1) return 2;
        *integer_result = left % right;
        return 0;
    default:
        return 2;
    }
}

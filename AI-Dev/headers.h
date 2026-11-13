#ifndef HEADERS_H
#define HEADERS_H

typedef enum {
    OP_SUM = 1,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_REMAINDER
} Operation;

/* Returns 0 on success, 1 for division by zero, 2 for integer overflow. */
int calculate(Operation operation, long long left, long long right,
              long long *integer_result, double *division_result);

#endif

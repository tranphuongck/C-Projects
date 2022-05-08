/*
make array_calculate_result && ./array_calculate_result
*/
#include "base.h"

typedef enum operation_type_e {
    OP_SET,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
} OperationType;

typedef struct operation_s {
    int position;
    OperationType type;
} Operation;

// Calculate the result based on a value in Values array and type of operation
double calculate(double * values, Operation * operations, int operations_count) {
    double result = 0;
    // todo: implement
    for (int i = 0; i < operations_count; i++) {
        switch (operations[i].type)
        {
        case OP_ADD:
            result += values[operations[i].position];
            break;
        case OP_SUB:
            result -= values[operations[i].position];
            break;
        case OP_MUL:
            result *= values[operations[i].position];
            break;
        case OP_DIV:
            result /= values[operations[i].position];
            break;
        default:
            result = values[operations[i].position];
            break;
        }
    }
    return result;
}

void test() {
    double values[8] = {0., 1., 16., 4., -1., -2., 10., 100.};

    test_within_d(calculate(values, NULL, 0), 0, 0.001);

    Operation op_1[4] = {{1, OP_ADD}, {2, OP_MUL}, {3, OP_DIV}, {5, OP_SUB}};
    test_within_d(calculate(values, op_1, 4), 6., 0.001); // (((0 + 1) * 16) / 4) - (-2) = 6

    Operation op_2[4] = {{7, OP_SET}, {6, OP_DIV}, {6, OP_DIV}, {1, OP_SUB}};
    test_within_d(calculate(values, op_2, 4), 0., 0.001); // ((100.0 / 10.0) / 10.0) - 1 = 0

    Operation op_3[2] = {{2, OP_ADD}, {4, OP_MUL}};
    test_within_d(calculate(values, op_3, 2), -16., 0.001); // (0 + 16) * (-1) = -16

    Operation op_4[1] = {{1, OP_SUB}};
    test_within_d(calculate(values, op_4, 1), -1., 0.001); // (0 - 1) = -1

    Operation op_5[6] = {{1, OP_SUB}, {4, OP_ADD}, {5, OP_DIV}, {0, OP_SUB}, {7, OP_MUL}, {6, OP_SUB}};
    test_within_d(calculate(values, op_5, 6), 90., 0.001); // (((((0 - 1) + (-1)) / (-2)) - 0) * 100) - 10 = 90
}

int main() {
    test();
    return 0;
}
/*
make rotate_array && ./rotate_array
*/

#include "base.h"

// Purpose statement.
void rotate(int* a, int n, int r) {
    require_not_null(a);
    require("not negative", n >= 0);
    // todo: implement
    // create a temporary array: int b[n];
    int* b = xcalloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        int index = i - r;
        if (index < 0) b[n + index] = a[i];
        else if (index >= n) b[0 + (n - index)] = a[i];
        else b[index] = a[i];
    }
    for (int i = 0; i < n; i++) {
        a[i] = b[i];
    }
}

void test(void) {
    Array ia, ib;
    int a[] = { 1, 2, 3, 4, 5 };
    int n = sizeof(a) / sizeof(a[0]);
    int b[] = { 1, 2, 3, 4, 5 };
    rotate(a, n, 0);
    ia = a_of_buffer(a, n, sizeof(int));
    ib = a_of_buffer(b, n, sizeof(int));
    ia_test_equal(ia, ib);

    int a2[] = { 1, 2, 3, 4, 5 };
    int b2[] = { 2, 3, 4, 5, 1 };
    rotate(a2, n, 1);
    ia = a_of_buffer(a2, n, sizeof(int));
    ib = a_of_buffer(b2, n, sizeof(int));
    ia_test_equal(ia, ib);

    int a3[] = { 1, 2, 3, 4, 5 };
    int b3[] = { 3, 4, 5, 1, 2 };
    rotate(a3, n, 2);
    ia = a_of_buffer(a3, n, sizeof(int));
    ib = a_of_buffer(b3, n, sizeof(int));
    ia_test_equal(ia, ib);

    int a4[] = { 1, 2, 3, 4, 5 };
    int b4[] = { 1, 2, 3, 4, 5 };
    rotate(a4, n, 5);
    ia = a_of_buffer(a4, n, sizeof(int));
    ib = a_of_buffer(b4, n, sizeof(int));
    ia_test_equal(ia, ib);

    int a5[] = { 1, 2, 3, 4, 5 };
    int b5[] = { 5, 1, 2, 3, 4 };
    rotate(a5, n, -1);
    ia = a_of_buffer(a5, n, sizeof(int));
    ib = a_of_buffer(b5, n, sizeof(int));
    ia_test_equal(ia, ib);
}

int main(void) {
    test();
    return 0;
}
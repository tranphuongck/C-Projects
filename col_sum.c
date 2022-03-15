/*
make col_sum && ./col_sum
*/

#include "base.h"

// Calculate the sum of matrix columns
int* col_sum(int* a, int rows, int cols) {
    // implement
    int matrix_size = rows * cols;
    int* result = xcalloc(cols,sizeof(int));
    for(int i = 0; i < cols; i++){
        for(int j = i; j < matrix_size; j += cols){
            result[i] += a[j];
        }
    }
    return result;
}

void test(void) {
    int a[3][3] = {
        { 1, -1, 3 }, 
        { 2, -2, 4 }, 
        { 3, -3, 5 }, 
    };
    int b[2][3] = {
        {1, 4, 2},
        {5, 7, 7},
    };
    int c[3][2] = {
        {1, 3},
        {2, 4},
        {5, 8},
    };

    printiln(a[0][0]);
    //a[0][0] + a[1][0] + a[2][0] == 6
    //a[0][1] + a[1][1] + a[2][1] == -6
    //a[0][2] + a[1][2] + a[2][2] == 12
    int* margin = col_sum((int*)a, 3, 3);
    int* margin2 = col_sum((int*)b, 2, 3);
    int* margin3 = col_sum((int*)c, 3, 2);
    int expected[] = { 6, -6, 12 };
    int expected2[] = {6, 11, 9};
    int expected3[] = {8, 15};
    ia_test_equal(a_of_buffer(margin, 3, sizeof(int)), 
                  a_of_buffer(expected, 3, sizeof(int)));
    ia_test_equal(a_of_buffer(margin2, 3, sizeof(int)), 
                  a_of_buffer(expected2, 3, sizeof(int)));
    ia_test_equal(a_of_buffer(margin3, 2, sizeof(int)), 
                  a_of_buffer(expected3, 2, sizeof(int)));
}

int main(void) {
    test();
    return 0;
}
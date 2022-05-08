/*
Compile: make four_sorted_digits
Run: ./four_sorted_digits
Compile and run:
make four_sorted_digits && ./four_sorted_digits
*/

#include "base.h"

// Purpose statement.
bool four_sorted_digits(String s) {
    // todo: implement
    int l = s_length(s);
    if (l == 0) return false;
    for (int i = 0; i < l - 3; i++) {
        int j = i + 1;
        while (j < i + 4 && )
    }
}

void four_sorted_digits_test(void) {
    test_equal_b(four_sorted_digits(""), false);
    test_equal_b(four_sorted_digits("123"), false);
    test_equal_b(four_sorted_digits("abcd"), false);
    test_equal_b(four_sorted_digits("1234"), true);
    test_equal_b(four_sorted_digits("2479"), true);
    test_equal_b(four_sorted_digits("1111"), true);
    test_equal_b(four_sorted_digits("a123"), false);
    test_equal_b(four_sorted_digits("123a"), false);
    test_equal_b(four_sorted_digits("1234a"), true);
    test_equal_b(four_sorted_digits("xx1234y"), true);
    test_equal_b(four_sorted_digits("abc12345"), true);
    test_equal_b(four_sorted_digits("a 1 2 3 4 c"), false);
    test_equal_b(four_sorted_digits("a 3333 c"), true);
}

int main(void) {
    report_memory_leaks(true);
    four_sorted_digits_test();
    return 0;
}
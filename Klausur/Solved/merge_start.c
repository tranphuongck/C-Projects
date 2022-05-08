/*
make merge_start && ./merge_start
*/

#include "base.h"

// Checks if s starts with prefix.
bool starts_with(String s, String prefix) {
    require_not_null(s);
    require_not_null(prefix);
    while (*prefix) {
        if (*s != *prefix) return false;
        s++;
        prefix++;
    }
    return true;
}

// <purpose statement>
String merge_prefix(String* a, int n, String prefix) {
    require_not_null(a);
    require("not negative", n >= 0);
    require_not_null(prefix);
    // implement
    int m = 0;
    for (int i = 0; i < n; i++) {
        if (starts_with(a[i], prefix)) m = m + strlen(a[i]) + 1;
    }
    if (m < 0) m = 0;
    printf("m = %i\n", m);

    char *str = (char*) xmalloc((m - 3) * sizeof(char));
    int index = 0;
    for (int i = 0; i < n; i++) {
        if (starts_with(a[i], prefix)) {
            for (int j = 0; j < strlen(a[i]); j++) {
                str[index] = a[i][j];
                index++;
            }
            str[index] = ' ';
            index++;
        }
    }
    return str;
}

void test(void) {
    String a[] = { "abc", "xya", "abx", "xyz", "ab", "aKx" };
    int n = sizeof(a) / sizeof(char*);
    printiln(n);
    test_equal_s(merge_prefix(a, n, "ab"), "abc abx ab ");
    test_equal_s(merge_prefix(a, n, "xy"), "xya xyz ");
    test_equal_s(merge_prefix(a, n, ""), "abc xya abx xyz ab aKx ");
    test_equal_s(merge_prefix(a, n, "k"), "");
    test_equal_s(merge_prefix(a, n, "a"), "abc abx ab aKx ");
}

int main(void) {
    test();
    return 0;
}
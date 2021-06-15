/*
    make string_replace
    ./string_replace
    make string_replace && ./string_replace
*/
#include "base.h"


char* next_occurence(char* s, char* find){
    //todo:
    require_not_null(s);
    int i = 0;
    int j = 0;
    while (i < strlen(s)) {
        if (s[i] == find[j]) {
            while (s[i] == find[j] && i < strlen(s)) {
                i++;
                j++;
            }
            if (j == strlen(find)) {
                s = s + (i - strlen(find));
                break;
            }
        }
        else {              
            i++;
            if (s[i] == '\0') {
                s = NULL;
                break;
            }
        }
        j = 0;
    }
    return s;
}

void test_next_occurence(){
    test_equal_s(next_occurence("aabbccdd", "aa"), "aabbccdd");
    test_equal_b(next_occurence("abbccdd", "aa") == NULL, true);
    test_equal_b(next_occurence("d", "aa") == NULL, true);
    test_equal_s(next_occurence("abbccdda", "a"), "abbccdda");
    test_equal_s(next_occurence("bccdda", "a"), "a");
    test_equal_s(next_occurence("hello, hello world", "hello"), "hello, hello world");
    test_equal_s(next_occurence("ello, hello world", "hello"), "hello world");
    test_equal_s(next_occurence("llo, hello world", "rld"), "rld");
    test_equal_b(next_occurence("hello, hello world", "bye") == NULL, true);
    test_equal_s(next_occurence("bbccdda", "aa"), "asdas");
}

int count(char* s, char* find){
    //todo:
    require_not_null(s);
    require_not_null(find);
    int times = 0;
    s = next_occurence(s, find);
    while (s!= NULL) {
        times++;
        s = s + strlen(find);
        s = next_occurence(s, find);
    }
    return times;
}

void test_count(){
    test_equal_i(count("aabbccdd", "aa"), 1);
    test_equal_i(count("abbccdda", "aa"), 0);
    test_equal_i(count("aaaabbaadd", "aa"), 3);
    test_equal_i(count("aabbccdd", "a"), 2);
    test_equal_i(count("aabbccdd", "abbc"), 1);
    test_equal_i(count("Die Uhrzeit ist 3:10", "Uhrzeit"), 1);
    test_equal_i(count("hello, hello world", "hello"), 2);
    test_equal_i(count("hello, hello world", "lo"), 2);
}

void copy(char* src, char* dst, int n) {
    src = xmalloc(sizeof(src) + 1);
    dst = xmalloc(sizeof(dst) + 1);
    require("valid n", n < strlen(dst));
    for (int i = 0; i < n; i++) {
        dst[i] = src[i];
    }
    dst[n] = '\0';
}

char* replace(char* s, char* find, char* replace_by){
    //todo:
    require_not_null(replace_by);
    char* replaced;
    int times = count(s, find);
    replaced = xmalloc(strlen(s) + (strlen(replace_by) - strlen(find)) * times + 1);
    while (times--) {

    }
    return s;
}

void test_replace(){
    test_equal_s(replace("aabbccdd", "a", "d"), "ddbbccdd");
    test_equal_s(replace("aaabbccdd", "aa", "d"), "dabbccdd");
    test_equal_s(replace("aabbccdd", "aa", "d"), "dbbccdd");
    test_equal_s(replace("aabbccdd", "b", "olo"), "aaolooloccdd");
    test_equal_s(replace("aabbccdd", "c", ""), "aabbdd");
    test_equal_s(replace("hello, hello world", "hello", "bye"), "bye, bye world");
    test_equal_s(replace("aabbccdd", "dd", "eee"), "aabbcceee");
    test_equal_s(replace("for(int x = X; x < X * 3; x++){printiln(x);}", "X", "90"), "for(int x = 90; x < 90 * 3; x++){printiln(x);}");
}

int main(void){
    test_next_occurence();
    test_count();
    //test_replace();
    //char* s = "abbccdda";
    //char* a = next_occurence(s, "bb");
    //char b[100];
    //copy(s, b, 5);
    //char* find = "abc";
    //char* a = next_occurence("abbccdd", "aa");
    //printf("%s\n", a);
    //printf("%s\n", b);
    return 0;
}
    
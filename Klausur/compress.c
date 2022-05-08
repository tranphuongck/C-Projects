/*
make compress && ./compress
*/
#include "base.h"

// Compress the string with the number of characters
String compress(String s) {
    require_not_null(s);
    // todo: implement
    if(strlen(s) == 0) return "";
    int len = strlen(s);
    int counter = 0;

    int a = 1;
    for(int i = 0; i < strlen(s); i++){
        if(s[i] ==  s[i + 1]) {
            a++;
            if(a > 2){
                len--;
                if(a > 9) len++;
            }
        }
        else a = 1;
    }

    String output = xmalloc(len);

    int count = 1;
    for(int i = 0; i < strlen(s); i++){
        int temp = i;
        if(s[i] == '\0') break;
        if(s[i] != s[i + 1]){
            output[counter] = s[i];
            counter++;
        }else{
            for(int j = i; j < strlen(s); j++) {
                if (s[j] == s[j + 1]) count++;
                else break;
            }
            if(count > 9){
                output[counter] = '0' + 9;
                output[counter + 1] = s[temp];
                if(count == 10){
                    output[counter + 2] = s[temp];
                    counter += 3;
                } 
                else {
                    output[counter + 2] = '0' + (count - 9);
                    output[counter + 3] = s[temp];
                    counter += 4;
                }
                i = temp + count - 1;
                count = 1;
            }
            else {
                output[counter] = '0' + count;
                output[counter + 1] = s[temp];
                counter += 2;
                i = temp + count - 1;
                count = 1;
            }
        }
    }

    for(int i = 0; i < strlen(output); i++){
        if(output[i] == '?') output[i] = '\0';
    }

    return output;
}

void test(void) {
    test_equal_s(compress(""), "");
    test_equal_s(compress("Sample String"), "Sample String");
    test_equal_s(compress("Hello World"), "He2lo World");
    test_equal_s(compress("AAAABBBBCCCC"), "4A4B4C");
    test_equal_s(compress("AAAAAAAAAAAA"), "9A3A");
    test_equal_s(compress("AAAAAAAAAA"), "9AA");
    test_equal_s(compress("BAAAAAAAAAAAAB"), "B9A3AB");
    test_equal_s(compress("BAAAAAAAAAAAABBBBBBBBBB"), "B9A3A9BB");
    test_equal_s(compress("FFFdddBBBBBBeeeEee"), "3F3d6B3eE2e");
}

int main(void) {
    test();
    return 0;
}
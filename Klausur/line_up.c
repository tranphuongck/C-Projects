/*
make line_up && ./line_up
*/

#include "base.h"

// Represents a list node.
typedef struct Node Node;
struct Node {
    String value;
    Node* next;
};

// Creates a new list node.
Node* new_node(String value, Node* next) {
    Node* node = xcalloc(1, sizeof(Node));
    node->value = value;
    node->next = next;
    return node;
}

//Add value to end of list
Node* append_list(Node* list, String value) {
	if(list == NULL){
		return new_node(value, NULL);
	} else {
		Node* node = list;
		while(node->next != NULL){ 
			node = node->next;  
		}	
		node->next = new_node(value, NULL);
		return list;
	}
}

// <purpose statement>
int line_up(String s, int cursor) {
    require_not_null(s);
    int n = strlen(s);
    require("valid cursor", 0 <= cursor && cursor <= n);
    // todo: implement
    String temp = s;
    String splt = "\n";
    String ptr = strtok(temp, splt);
    while (ptr != NULL) {
        printf("%s\n", ptr);
        ptr = strtok(NULL, splt);
    }
    return cursor;
}

void test(void) {
    test_equal_i(line_up("", 0), 0);
    test_equal_i(line_up("xxx", 0), 0);
    test_equal_i(line_up("xxx", 3), 3);
    //                    01 23
    test_equal_i(line_up("x\nx", 2), 0);
    //                    01234 56789 0123
    test_equal_i(line_up("abcd\nefgh\nijk", 0), 0);
    test_equal_i(line_up("abcd\nefgh\nijk", 3), 3);
    test_equal_i(line_up("abcd\nefgh\nijk", 4), 4);
    test_equal_i(line_up("abcd\nefgh\nijk", 5), 0);
    test_equal_i(line_up("abcd\nefgh\nijk", 6), 1);
    test_equal_i(line_up("abcd\nefgh\nijk", 9), 4);
    test_equal_i(line_up("abcd\nefgh\nijk", 10), 5);
    test_equal_i(line_up("abcd\nefgh\nijk", 11), 6);
    test_equal_i(line_up("abcd\nef\nghijk", 12), 7);
}

int main(void) {
    test();
    return 0;
}
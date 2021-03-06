/*
make at_most_two && ./at_most_two
*/

#include "base.h"

// Represents a list node.
typedef struct Node Node;
struct Node {
    int value;
    Node* next;
};

// Creates a new list node.
Node* new_node(int value, Node* next) {
    Node* node = xcalloc(1, sizeof(Node));
    node->value = value;
    node->next = next;
    return node;
}

// Prints the list into the given file.
void fprint_list(char* filename, Node* list) {
    require_not_null(filename);
    FILE* f = fopen(filename, "w");
    fprintf(f, "[");
    for (Node* n = list; n; n = n->next) {
        fprintf(f, "%d", n->value);
        if (n->next) fprintf(f, ", ");
    }
    fprintf(f, "]");
    fclose(f);
}

// Counts the number of times x appears in list.
int count(Node* list, int x) {
    // todo: implement
    int c = 0;
    for (Node* node = list; node; node = node->next) {
        if (node->value == x) c++;
    }
    return c;
}

Node* append_list(Node* list, int value) {
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

Node* reverse_list (Node* list) {
    if (list == NULL) return list;
    else {
        Node *prev = NULL;
        Node *current = list;
        Node *next = NULL;
        while (current != NULL) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        list = prev;
        return prev;
    }
}

// Creates a result list from the input list, keeping only the first and second appearance of a value. For example, input list [3, 1, 3, 2, 3, 5, 1, 1] would become [3, 1, 3, 2, 5, 1], removing the third 3 and the third 1. Maintains the original order. Does not change the input list.
Node* at_most_two(Node* list) {
    // todo: implement
    Node *reversed = reverse_list(list);
    Node *output = NULL;
    for (Node *n = reversed; n; n = n->next) {
        if (count(n, n->value) <= 2) output = append_list(output, n->value);
    }
    return reverse_list(output);
}

void test(void) {
    Node *list0, *list;

    Node* list_a = new_node(1, new_node(2, new_node(1, new_node(2, new_node(1, NULL)))));
    test_equal_i(count(list_a, 4), 0);
    test_equal_i(count(list_a, 1), 3);
    test_equal_i(count(list_a, 2), 2);

    list0 = NULL;
    list = at_most_two(list0);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[]");

    list0 = new_node(1, new_node(1, new_node(1, new_node(1, NULL))));
    list = at_most_two(list0);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[1, 1]");

    list0 = new_node(1, new_node(2, new_node(1, new_node(2, new_node(1, new_node(2, NULL))))));
    list = at_most_two(list0);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[1, 2, 1, 2]");

    list0 = new_node(1, new_node(1, new_node(1, new_node(3, new_node(1, NULL)))));
    list = at_most_two(list0);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[1, 1, 3]");

    list0 = new_node(3, new_node(1, new_node(3, new_node(2, new_node(3, new_node(5, new_node(1, new_node(1, NULL))))))));
    list = at_most_two(list0);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[3, 1, 3, 2, 5, 1]");

}

int main(void) {
    test();
    return 0;
}
/*
make crop_list && ./crop_list
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

// Counts the number of values in list.
int length_list(Node* list) {
    // todo: implement
    int count = 0;
    for (Node* n = list; n; n = n->next) {
        count++;
    }
    return count;
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

// Creates a result list from the input list, by removing the first r and the last r elements from the input list. 
//For example, crop([1, 2, 3, 4], 1) becomes [2, 3]. Maintains the original order of the remaining elements. Does not change the input list.
Node* crop_list(Node* list, int r) {
    require("not negative", r >= 0);
    // todo: implement
    Node* node = list;
    Node* output1 = NULL;

    int index = 1;
    for (Node* n = node; n; n = n->next) {
        if (index > r) output1 = append_list(output1, n->value);
        index++;
    }
    
    Node* output2 = NULL;
    index = 1;
    output1 = reverse_list(output1);
    for (Node* n = output1; n; n = n->next) {
        if (index > r) output2 = append_list(output2, n->value);
        index++;
    }
    return reverse_list(output2);
}

void test(void) {
    Node *list0, *list;

    Node* list_a = NULL;
    test_equal_i(length_list(list_a), 0);

    list_a = new_node(1, list_a);
    test_equal_i(length_list(list_a), 1);

    list_a = new_node(2, list_a);
    test_equal_i(length_list(list_a), 2);

    list_a = new_node(3, list_a);
    test_equal_i(length_list(list_a), 3);

    list0 = NULL;
    list = crop_list(list0, 1);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[]");

    list0 = new_node(1, new_node(2, new_node(3, new_node(4, NULL))));
    list = crop_list(list0, 0);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[1, 2, 3, 4]");

    list0 = new_node(1, new_node(2, new_node(3, new_node(4, NULL))));
    list = crop_list(list0, 1);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[2, 3]");

    list0 = new_node(1, new_node(2, new_node(3, new_node(4, NULL))));
    list = crop_list(list0, 2);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[]");

    list0 = new_node(1, new_node(2, new_node(3, new_node(4, NULL))));
    list = crop_list(list0, 3);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[]");

    list0 = new_node(0, new_node(1, new_node(2, new_node(3, new_node(4, NULL))))); //[0, 2, 4]
    list = crop_list(list0, 2);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[2]");

    list0 = new_node(0, new_node(1, new_node(2, new_node(3, new_node(4, NULL)))));
    list = crop_list(list0, 3);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[]");
}

int main(void) {
    test();
    return 0;
}
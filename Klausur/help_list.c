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

//Reverse list
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

//Add value to start of list
Node* prepend_list(Node* list, int value) {
    return new_node(value, list);
}

//Add value to end of list
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

int main(void) {
    return 0;
}
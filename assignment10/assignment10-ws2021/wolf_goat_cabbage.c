/*
Compile: make wolf_goat_cabbage
Run: ./wolf_goat_cabbage
make wolf_goat_cabbage && ./wolf_goat_cabbage
*/

#include "base.h"

// Represents a single list node. The value is dynamically allocated. The node 
// is the owner of the value and has to free it when itself is released.
struct Node {
    String value; // dynamically allocated string, release memory!
    struct Node* next; // self-reference
};
typedef struct Node Node;

// Create a list node. Copies the value (into dynamically allocated storage).
Node* new_node(String value, Node* next) {
    Node* node = xcalloc(1, sizeof(Node));
    node->value = s_copy(value); // s_copy performs dynamic allocation
    node->next = next;
    return node;
}

// Prints the components of the given list.
void print_list(Node* list) {
    if (list == NULL) {
        printf("[]");
    } else {
        printf("[%s", list->value);
        for (Node* n = list->next; n != NULL; n = n->next) {
            printf(" %s", n->value);
        }
        printf("]");
    }
}

// Print list followed by a newline.
void println_list(Node* list) {
    print_list(list);
    printsln("");
}

// Free all nodes of the list, including the values it contains.
void free_list(Node* list) {
    // todo: implement (Aufgabe 1)
    // (there will be memory leaks if this function is not yet implemented)
	Node* nnext = NULL;
	//läuft bis end of List
	for(Node* n = list; n != NULL; n = nnext){
		nnext = n->next;
		if(n->value != NULL) free(n->value); //wenn es noch value in list gibt, free alle Values.
		free(n);
	}
}


bool test_equal_lists(int line, Node* list1, Node* list2);

/*
Example calls for test_equal_lists.
Expected output (line numbers may differ):
Line 63: The lists are equal.
Line 66: The lists are equal.
Line 70: The lists are equal.
Line 74: The values at node 0 differ: hello <-> you.
Line 78: The lists are equal.
Line 82: The values at node 1 differ: second <-> hello.
Line 86: list1 is shorter than list2.
Line 90: list1 is longer than list2.
*/
void test_equal_lists_test(void) {
    Node* list1 = NULL;
    Node* list2 = NULL;
    test_equal_lists(__LINE__, list1, list2);
    
	list1 = new_node("hello", NULL);
    list2 = list1;
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1);
    
	list1 = new_node("hello", NULL);
    list2 = new_node("hello", NULL);
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    
	list1 = new_node("hello", NULL);
    list2 = new_node("you", NULL);
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    
	list1 = new_node("first", new_node("second", NULL));
    list2 = new_node("first", new_node("second", NULL));
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    
	list1 = new_node("first", new_node("second", NULL));
    list2 = new_node("first", new_node("hello", NULL));
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    
	list1 = new_node("first", new_node("second", NULL));
    list2 = new_node("first", new_node("second", new_node("third", NULL)));
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
    
	list1 = new_node("first", new_node("second", new_node("third", NULL)));
    list2 = new_node("first", new_node("second", NULL));
    test_equal_lists(__LINE__, list1, list2);
    free_list(list1); free_list(list2);
}

// Checking whether two string lists are equal.
bool test_equal_lists(int line, Node* list1, Node* list2) {
    // todo: implement (Aufgabe 1)
	int i = 0;
	while(true){
		
		//wenn alle Elemente von list1 und list2 gleich sind
		if(list1 == list2){
			printf("LINE %d: lists are equal \n", line);
			return true;
		}else if(list1 == NULL && list2 != NULL){ //wenn list1 gleich NULL ist und list2 nicht NULL ist
			printf("Line %d: list1 is shorter than list2.\n", line);
			return false;
		}else if(list1 != NULL && list2 == NULL){ //wenn list2 gleich NULL ist und list1 nicht NULL ist
			printf("Line %d: list1 is longer than list2.\n", line);
			return false;
		} else if(!s_equals(list1->value, list2->value)){ //wenn ein Element von list1 in position [i] nicht gleich das jeweiliches Element in list2
			printf("Line %d: The values at node %d differ: %s <-> %s.\n", line, i, list1->value, list2->value);
			return false;
		}
		list1 = list1->next; //liest weiter in endlist
		list2 = list2->next;
		i++;
	}
	
    return false;
}

int length_list(Node* list);

// Example calls for length_list (below).
void length_list_test(void) {
    // todo: implement (Aufgabe 1)
    // todo: at least 3 checks, with test_equal_i(actual, expected);
	
	Node* ls = NULL;
	test_equal_i(length_list(ls), 0);
	
	ls = new_node("abc", NULL);
	test_equal_i(length_list(ls), 1);
	free_list(ls);
	
	ls = new_node("abc", new_node("cde", new_node("ghk", NULL)));
	test_equal_i(length_list(ls), 3);
	free_list(ls);
}

// Number of elements of the list.
int length_list(Node* list) {
    int n = 0;
    for (Node* node = list; node != NULL; node = node->next) n++;
    return n;
}

int index_list(Node* list, String s);

// Example calls for index_list (below).
void index_list_test(void) {
    // todo: implement (Aufgabe 1)
    // todo: at least 3 checks, with test_equal_i(actual, expected);
	Node* ls = NULL;
	test_equal_i(index_list(ls, "abc"), -1);
	
	ls = new_node("abc", new_node("cdf", NULL));
	test_equal_i(index_list(ls, "cdf"), 1);
	free_list(ls);
	
	ls = new_node("abc", new_node("cdf", new_node("ghk", new_node("mnp", NULL))));
	test_equal_i(index_list(ls, "mnp"), 3);
	free_list(ls);
}

// Return index of s in list, or -1 if s is not in list.
int index_list(Node* list, String s) {
    // todo: implement (Aufgabe 1)
	int index = 0;
	for(Node* n = list; n != NULL; n = n->next){
		//vergleich string s und value in list
		//wenn es true ist, return index von element in list
		if(s_equals(n->value, s)){
			return index;
		}
		index++;
	}
    return -1;
}

// Check whether list contains s.
bool contains_list(Node* list, String s) {
    return index_list(list, s) >= 0;
}

Node* remove_list(Node* list, int index);

// Example calls for remove_list (below).
void remove_list_test(void) {
    // todo: implement (Aufgabe 1)
    // todo: at least 3 checks, with test_equal_lists(__LINE__, actual, expected);
	Node* ls = NULL;
	Node* ls1 = NULL;
	ls1 = remove_list(ls, 1);
	test_equal_lists(__LINE__, ls1, ls);
	free_list(ls1);
	
	
	ls = new_node("abc", new_node("def", NULL));
	ls = remove_list(ls, 0);
	ls1 = new_node("def", NULL);
	test_equal_lists(__LINE__, ls, ls1);
	free_list(ls);
	free_list(ls1);
	
	ls = new_node("abc", new_node("def", new_node("ghk", NULL)));
	ls = remove_list(ls, 2);
	ls1 = new_node("abc", new_node("def", NULL));
	test_equal_lists(__LINE__, ls, ls1);
	free_list(ls);
	free_list(ls1);
}

// Remove element at position index from list. The element at index has to be deleted.
Node* remove_list(Node* list, int index) {
    // todo: implement (Aufgabe 1)
	require("valid input", index >= 0);
	if(list == NULL) return list;
	
	//einfügen in erste Element
	if(index == 0){
		//New_list ist die List aber ab zweite Element
		Node* new_list = list->next;
		free(list->value);
		free(list);
		return new_list;
	}
	
	//einfügen ab zweite Element
	int count = 0;
	for(Node* n = list; n != NULL; n = n->next){
		//[ 0,   1,   2,   3 ]
		//["a", "d", "g", "h"]
		if(count + 1 == index){
			Node* remove_node = n->next; //element[count+1] in list
			if(remove_node == NULL) return list; //remove_node in index Position ist letzte Node
			
			Node* node_next = remove_node->next; //element[count+2] in list
			free(remove_node->value);
			free(remove_node);
			n->next = node_next; //assignt next node in list is element[count+2]
			return list;
		}
		count++;
	}
    return list;
}

///////////////////////////////////////////////////////////////////////////

// The boat may either be at the left or right river bank. 
// We don't care for the transition (boat crossing the river).
enum Position {
    LEFT, RIGHT
};

// The data that represents the state of the puzzle.
typedef struct {
    // List of objects on the left river bank.
    Node* left;

    // List of objects on the right river bank.
    Node* right;

    // List of objects in the boat. The boat has a capacity of one object only.
    Node* boat;

    // Current boat position.
    enum Position position;
} Puzzle;

// Initialize the state of the puzzle.
Puzzle make_puzzle(void) {
    Puzzle p = { new_node("Wolf", new_node("Ziege", new_node("Kohl", NULL))), NULL, NULL, LEFT };
    return p;
}

// Print the current state of the puzzle.
void print_puzzle(Puzzle* p) {
    // todo: implement (Aufgabe 2)
    switch (p->position) {
    case LEFT:
        print_list(p->left);
        print_list(p->boat);
        printf("\t\t");
        print_list(p->right);
        println();
        break;  
    case RIGHT:
        print_list(p->left);
        printf("\t\t");
        print_list(p->boat);
        print_list(p->right);
        println();
        break;  
    }
}

// Release memory and quit.
void finish_puzzle(Puzzle* p) {
    // todo: implement (Aufgabe 2)
    free_list(p->left);
    free_list(p->boat);
    free_list(p->right);
    exit(0);
}

bool test_equal_puzzle(int line, Node* list1, Node* list2) {
    int i = 0;
    while (true) {
        if (list1 == list2) {
            return true;
        }
        else if (list1 == NULL && list2 != NULL) {
            return false;
        }
        else if(list1 != NULL && list2 == NULL) {
            return false;
        }
        else if (!s_equals(list1->value, list2->value)) {
            return false;
        }
        list1 = list1->next;
        list2 = list2->next;
        i++;
    }
    return false;
}

void evaluate_puzzle(Puzzle* p) {
    // todo: implement (Aufgabe 2)
    //Fail case 1: Wolf & Goat   
    if (contains_list(p->left, "Wolf") == true && contains_list(p->left, "Ziege") == true && contains_list(p->left, "Kohl") == false && p->position == RIGHT) {
        printf("The wolf ate the goat!\n");
        finish_puzzle(p);
    }
    else if (contains_list(p->right, "Wolf") == true && contains_list(p->right, "Ziege") == true && contains_list(p->right, "Kohl") == false && p->position == LEFT) {
        printf("The wolf ate the goat!\n");
        finish_puzzle(p);
    }
    //Fail case 2: Goat & Cabbage
    else if (contains_list(p->left, "Wolf") == false && contains_list(p->left, "Ziege") == true && contains_list(p->left, "Kohl") == true && p->position == RIGHT) {
        printf("The goat ate the cabbage!\n");
        finish_puzzle(p);
    }
    else if (contains_list(p->right, "Wolf") == false && contains_list(p->right, "Ziege") == true && contains_list(p->right, "Kohl") == true && p->position == LEFT) {
        printf("The goat ate the cabbage!\n");
        finish_puzzle(p);
    }
    else if (contains_list(p->right, "Wolf") == true && contains_list(p->right, "Ziege") == true && contains_list(p->right, "Kohl") == true) {
        printf("Transport succeed!\n");
        finish_puzzle(p);
    }
    else {
        printf("Keep up...\n");
    }
}

//Help function, from mensa.c 
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

void play_puzzle(Puzzle* p) {
    // todo: implement (Aufgabe 2)
    print_puzzle(p);
    while (true) {
        String input = s_input(100);
        if (s_equals(input, "q") == true) exit(0);
        if (s_equals(input, "cheat") == true) p->right = new_node("Wolf", new_node("Ziege", new_node("Kohl", NULL))); //for debugging
        //Phase 1: move object from left bank to boat
        //Phase 2: move boat from left bank to right bank
        //Phase 3: move object from boat to right bank
        //Phase 4: move boat from right bank to left bank, back to Phase 1
        if (p->position == LEFT) {
            if (s_equals(input, "r") == true) p->position = RIGHT; //switch boat position
            else if (contains_list(p->left, input) == true && length_list(p->boat) < 1) {//riverbank contains object and boat empty
                p->left = remove_list(p->left, index_list(p->left, input));
                p->boat = new_node(input, NULL);
            }
            else if (contains_list(p->left, input) == true && length_list(p->boat) == 1) printf("The boat can only carry one object.\n"); //boat already carrying object
            else if (contains_list(p->boat, input) == true) {//move object from boat back to riverbank
                p->left = append_list(p->left, input);
                p->boat = remove_list(p->boat, 0);
            }
        }
        if (p->position == RIGHT) {
            if (s_equals(input, "l") == true) p->position = LEFT; //switch boat position
            else if (contains_list(p->right, input) == true && length_list(p->boat) < 1) {//riverbank contains object and boat empty
                p->right = remove_list(p->right, index_list(p->right, input));
                p->boat = new_node(input, NULL);
            }
            else if (contains_list(p->right, input) == true && length_list(p->boat) == 1) printf("The boat can only carry one object.\n"); //boat already carrying object
            else if (contains_list(p->boat, input) == true) {//move object from boat back to riverbank
                p->right = append_list(p->right, input);
                p->boat = remove_list(p->boat, 0);
            }
        }
        s_free(input);
        print_puzzle(p);
        evaluate_puzzle(p);
    }
}

///////////////////////////////////////////////////////////////////////////


int main(void) {
    report_memory_leaks(true);

    test_equal_lists_test();
    length_list_test();
    index_list_test();
    remove_list_test();
	
	Puzzle p = make_puzzle();
    //print_puzzle(&p);
    //evaluate_puzzle(&p);
    play_puzzle(&p);
    return 0;
}

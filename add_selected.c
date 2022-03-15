/*
make add_selected && ./add_selected
*/

#include "base.h"

// Represents a binary tree with integer values.
typedef struct Tree {
    int value;
    struct Tree *left;
    struct Tree *right;
} Tree;

// Creates a new binary tree node.
Tree* new_tree(Tree* left, int value, Tree* right) {
    Tree* n = xcalloc(1, sizeof(Tree));
    n->left = left;
    n->value = value;
    n->right = right;
    return n;
}

// <purpose statement>
int add_selected(Tree* t, String path, int sum) {
    // implement
    /* Ohne rekursiv
    if (t == NULL) return 0;
    while (path[0] != '\0') {
        if (t == NULL) break;
        if (path[0] == '+') sum += t->value;
        if (path[0] == 'r') t->left;
        if (path[0] == 'l') t->right;
        path++;
    }
    */
    //Mit rekursiv
    String p = path + 1;
    if (t == NULL || path[0] == '\0') return 0;
    if (path[0] == '+') sum = t->value + add_selected(t, p, sum);
    if (path[0] == 'l') sum += add_selected(t->left, p, sum);
    if (path[0] == 'r') sum += add_selected(t->right, p, sum);
    return sum;
}

// Creates a leaf node.
Tree* leaf(int value) {
    return new_tree(NULL, value, NULL);
}

// Creates a node.
Tree* node(Tree* left, int value, Tree* right) {
    return new_tree(left, value, right);
}

void test(void) {
    Tree* t;
    //    1
    //  2   5
    // 7 3 4 6
    t = node(node(leaf(7), 2, leaf(3)), 1, node(leaf(4), 5, leaf(6)));
    test_equal_i(add_selected(t, "+", 0), 1);
    test_equal_i(add_selected(t, "++", 0), 2);
    test_equal_i(add_selected(t, "rrrr+", 0), 0);
    test_equal_i(add_selected(t, "+r", 0), 1);
    test_equal_i(add_selected(t, "r+", 0), 5);
    test_equal_i(add_selected(t, "+r+", 0), 1 + 5);
    test_equal_i(add_selected(t, "+r+r", 0), 1 + 5);
    test_equal_i(add_selected(t, "+r+r+", 0), 1 + 5 + 6);
    test_equal_i(add_selected(t, "rl+", 0), 4);
    test_equal_i(add_selected(t, "+lr+", 0), 1+3);
    test_equal_i(add_selected(t, "lr", 0), 0);
}

int main(void) {
    test();

    return 0;
}
/*
make min_leaf_level && ./min_leaf_level
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

// Prints a tree.
void print_tree(Tree* n) {
    if (n == NULL) {
        prints("_");
    } else if (n->left == NULL && n->right == NULL) {
        prints("(");
        printi(n->value);
        prints(")");
    } else {
        prints("(");
        print_tree(n->left);
        prints(", ");
        printi(n->value);
        prints(", ");
        print_tree(n->right);
        prints(")");
    }
}

// Prints a tree followed by a line break.
void print_tree_ln(Tree* n) {
    print_tree(n);
    printsln("");
}

// Checks if n is a leaf (has no successors).
bool is_leaf(Tree* n) {
    return n != NULL && n->left == NULL && n->right == NULL;
}

// Returns the minimum level at which there is a leaf. The tree's root is at level 0.
int min_leaf_level(Tree* n, int level) {
    // todo: implement
    if (n == NULL) return level;
    if (n->left == NULL && n->right == NULL) return level;
    if (n->left == NULL) return min_leaf_level(n->right, level) + 1;
    if (n->right == NULL) return min_leaf_level(n->left, level) + 1;
    if (min_leaf_level(n->right, level) > min_leaf_level(n->left, level)) return min_leaf_level(n->left, level) + 1;
    else return min_leaf_level(n->right, level) + 1;
}

// Convenience function to create a leaf.
Tree* leaf(int value) {
    return new_tree(NULL, value, NULL);
}

// Convenience function to create a node.
Tree* node(Tree* left, int value, Tree* right) {
    return new_tree(left, value, right);
}

void test(void) {
    Tree* t;
    // one-element tree
    t = leaf(100);
    test_equal_i(min_leaf_level(t, 0), 0);
    
    //   1000
    // 124  110
    t = node(leaf(124), 1000, leaf(110));
    test_equal_i(min_leaf_level(t, 0), 1);
    
    //   1000
    // 124  NULL
    t = node(leaf(124), 1000, NULL);
    test_equal_i(min_leaf_level(t, 0), 1);
    
    //     1000
    // 124      NULL
    //1 NULL
    t = node(node(leaf(1), 124, NULL), 1000, NULL);
    test_equal_i(min_leaf_level(t, 0), 2);
    
    //       1
    //   2       3
    // 4 NULL
    t = node(node(leaf(4), 2, NULL), 1, leaf(3));
    test_equal_i(min_leaf_level(t, 0), 1);
    
    //       1
    //   2       3
    // 4   5
    t = node(node(leaf(4), 2, leaf(5)), 1, leaf(3));
    test_equal_i(min_leaf_level(t, 0), 1);
    
    //              1
    //       2            3
    //     4   NULL
    // NULL 5
    t = node(node(node(NULL, 4, leaf(5)), 2, NULL), 1, leaf(3));
    test_equal_i(min_leaf_level(t, 0), 1);
    
    //    1
    //  2   5
    // 3 4 6 7
    t = node(node(leaf(3), 2, leaf(4)), 1, node(leaf(6), 5, leaf(7)));
    test_equal_i(min_leaf_level(t, 0), 2);
    
    //       1
    //     2   3
    //   4
    // 5
    //  6
    t = node(node(node(NULL, 4, node(leaf(6), 5, NULL)), 2, NULL), 1, leaf(3));
    test_equal_i(min_leaf_level(t, 0), 1);
}

int main(void) {
    test();
    return 0;
}
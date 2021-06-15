
#include "computational_tree.h"
//print module

typedef struct TNode{
	TreeNode* tree;
	int level;
	int index;
	struct TNode* next;
}TNode;

void print_tree(TreeNode* tree);
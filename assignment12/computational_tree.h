#include "base.h"

#ifndef __COMP_TREE_H__
#define __COMP_TREE_H__

typedef enum Tag{
	FUNCTION, PARAMETER, CONSTANT
}Tag;

typedef double (*ComputationalFunction)(double a, double b);

typedef struct Function{
	ComputationalFunction f;
	char* string_representation;
}Function;

typedef struct Computational{
	Tag tag;
	union{
		Function* function;
		double constant;
		char* parameter;
	};
} Computational;

typedef struct ComputationalResult{
	bool valid; 
	double result;
}ComputationalResult;

typedef struct TreeNode{
	Computational* c;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

typedef struct PNode{
	char* name;
	double value;
	struct PNode* next;
}PNode;

TreeNode * new_tree_node(TreeNode* left, Computational* c, TreeNode* right);

#endif
//comp_tree_print.c
#include "comp_tree_print.h"

TNode* new_tnode(TreeNode* tree, TNode* next, int level, int index){
	TNode* t = xmalloc(sizeof(TNode));
	t->tree = tree;
	t->level = level;
	t->index = index;
	t->next = next;
	return t;
}

void append_tnode(TreeNode* tree, TNode* tn, int level, int index){
	if(tree == NULL || tree == NULL){
		return;
	}else{
		for(; tn->next != NULL; tn=tn->next);
		tn->next = new_tnode(tree, NULL, level, index);
	}
}

int max(int a, int b){
	return (a > b) ? a : b;
}

int max_depth(TreeNode* tree_node){
	if(tree_node == NULL)
		return 0;
	else{
		return 1 + max(max_depth(tree_node->left), max_depth(tree_node->right));
	}
}

//the above functions are helper functions for this tree print function
void print_tree(TreeNode* tree){
	if(tree == NULL){
		return;
	}
	TNode* tn = new_tnode(tree, NULL, 0, 0);
	int depth = max_depth(tree);
	
	int n = depth;
	char* element = "     ";
	double width_2 = strlen(element) / 2.0;
	int distance = 0;
	for(int i = 0; i < n - 1; i++){
		distance = (distance << 1);
		distance++;
	}
	for (int n = depth, a = 1; n > 0; n--, a = a * 2 ){
		while(n > 0){
			
			for(int i = 0; i < distance * width_2; i++ ){
				printf(" ");
			}
			
			for(int i= 0; i < a; i++){
				if(tn && tn->level == depth - n && tn->index == i){
					Computational* c = tn->tree->c;
					if(c->tag == FUNCTION){
						printf("( %s )", c->function->string_representation);
					}else if(c->tag == CONSTANT){
						printf("(%3.1f)", c->constant);
					}else if(c->tag == PARAMETER){
						printf("( %s )", c->parameter );
					}else{
						printf("( ? )");
					}
					
					append_tnode(tn->tree->left, tn, tn->level + 1, (tn->index << 1) + 0);
					append_tnode(tn->tree->right, tn, tn->level + 1, (tn->index << 1) + 1);
					TNode* to_free = tn;
					tn = tn->next;
					free(to_free);
					
				}else{
					printf(element);
				}

				for(int i = 0; i <  distance  * 2 * width_2 ;i++ ){
					printf(" ");
				}
			}
			
			a = a * 2;
			n--;

			distance = (distance >> 1);
			printf("\n");
		}
	}
	printf("\n");
	
}
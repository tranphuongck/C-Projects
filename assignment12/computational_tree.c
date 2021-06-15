#include "computational_tree.h"
#include "comp_tree_print.h"

//returns a pointer to a dynamically allocated TreeNode
TreeNode * new_tree_node(TreeNode* left, Computational* c, TreeNode* right){
	TreeNode* t = xmalloc(sizeof(TreeNode));
	t->left = left;
	t->right = right;
	t->c = c;
	return t;
}

//returns a pointer to a dynamically allocated TreeNode, left and right are NULL
TreeNode * new_leaf(Computational* c){
	TreeNode* t = xmalloc(sizeof(TreeNode));
	t->left = NULL;
	t->right = NULL;
	t->c = c;
	return t;
}

//checks whether two trees are equal
bool tree_equals_tree(TreeNode* t1, TreeNode* t2){
	if(t1 == t2){
		//both are NULL or the same tree.
		return true;
	}else if((t1 == NULL && t2 != NULL) || (t1 == NULL && t2 != NULL)){
		//one tree is NULL
		return false;
	}else{
		//both trees are not NULL
		if(t1->c->tag != t2->c->tag){
			return false;
		}else{
			switch(t1->c->tag){
				case FUNCTION:
					if(t1->c->function != t2->c->function){
						return false;
					} 
				break;
				case PARAMETER:
					if(strcmp(t1->c->parameter, t2->c->parameter) != 0){
						return false;
					}
				break;
				case CONSTANT:
					if(t1->c->constant != t2->c->constant){
						return false;
					}
				break;
			}
			return tree_equals_tree(t1->left, t2->left) &&  tree_equals_tree(t1->right, t2->right); 
		}
	}
}

//frees the memory allocated by a tree
void free_tree_node(TreeNode* tree_node){
	if(tree_node){
		Computational* c = tree_node->c;
		if(c->tag == PARAMETER){
			free(c->parameter);	
		}else if(c->tag == FUNCTION){
			free_tree_node(tree_node->left);
			free_tree_node(tree_node->right);
		}
		free(c);
		free(tree_node);
	}
}

//returns true if the tree_node is a constant
bool is_constant(TreeNode* tree_node){
	return tree_node != NULL && tree_node->c != NULL && tree_node->c->tag == CONSTANT;
}

//returns true if the tree_node is a parameter
bool is_parameter(TreeNode* tree_node){
	return tree_node != NULL && tree_node->c != NULL && tree_node->c->tag == PARAMETER;
}

//returns true if the tree_node is a function
bool is_function(TreeNode* tree_node){
	return tree_node != NULL && tree_node->c != NULL && tree_node->c->tag == FUNCTION;
}

//returns a pointer to a dynamically allocated PNode
PNode* new_pnode(char* name, double value, PNode* next){
	PNode* p = xmalloc(sizeof(PNode));
	p->name = s_copy(name);
	p->value = value;
	p->next = next;
	return p;
}

//frees the memory allocated by a pnode
void free_pnode(PNode* pnode){
	if(pnode){
		free(pnode->name);
		free_pnode(pnode->next);
		free(pnode);
	}
}

//returns a pointer to a dynamically allocated Computational representing a function
Computational* new_function(Function* function){
	Computational* c = xmalloc(sizeof(Computational));
	c->tag = FUNCTION;
	c->function = function;
	return c;
} 

//returns a pointer to a dynamically allocated Computational representing a constant
Computational* new_constant(double d){
	Computational* c = xmalloc(sizeof(Computational));
	c->tag = CONSTANT;
	c->constant = d;
	return c;
} 

//returns a pointer to a dynamically allocated Computational representing a parameter
Computational* new_parameter(char* p){
	Computational* c = xmalloc(sizeof(Computational));
	c->tag = PARAMETER;
	c->parameter = s_copy(p);
	return c;
} 

//creates a dynamically allocated copy of a Computational struct 
Computational* copy_computational(Computational* computational){
	if(computational == NULL){
		return NULL;
	}
	Computational* c = xmalloc(sizeof(Computational));
	c->tag = computational->tag;

	switch(c->tag){
		case FUNCTION:
			c->function = computational->function; 
		break;
		case PARAMETER:
			c->parameter = s_copy(computational->parameter);
		break;
		case CONSTANT:
			c->constant = computational->constant;
		break;
		
	}
	return c;
}



//supported functions for this task.
double plus(double a, double b){
	return a + b;
}

double minus(double a, double b){
	return a - b;
}

double times(double a, double b){
	return a * b;
}

double divide(double a, double b){
	return a / b;
}

//each function has a string representation for the printing
static Function add = {&plus, "+"};
static Function sub = {&minus, "-"};
static Function mul = {&times, "*"};
static Function divi = {&divide, "/"};


//evaluates a tree
ComputationalResult evaluate(TreeNode* comp_tree, PNode* parameter_list){
	//todo:
	ComputationalResult result = {false, 0.0};

	return result;
}

void test_evaluate(){
	printf("-----------------------\n");
	printf("Test evaluate function:\n");
	printf("-----------------------\n");
	PNode* parameter_list = new_pnode("x", 2.0, new_pnode("y", 3.0, new_pnode("z", -4.5, NULL)));
	
	ComputationalResult result;
	
	result = evaluate(NULL, NULL);	
	test_equal_b(result.valid, false);
	
	TreeNode* comp_tree = new_tree_node(new_leaf(new_constant(1.0)), new_function(&add), new_leaf(new_constant(-3.0)));
	print_tree(comp_tree);
	result = evaluate(comp_tree, NULL);	
	test_within_d(result.result, -2.0, 1.0e-6);
	test_equal_b(result.valid, true);
	free_tree_node(comp_tree);
	
	comp_tree = new_tree_node(new_leaf(new_constant(1.0)), new_function(&add), NULL);
	print_tree(comp_tree);
	result = evaluate(comp_tree, NULL);	
	test_equal_b(result.valid, false);
	free_tree_node(comp_tree);
	
	comp_tree = new_tree_node(NULL, new_function(&sub), new_leaf(new_constant(8.0)));
	print_tree(comp_tree);
	result = evaluate(comp_tree, NULL);	
	test_equal_b(result.valid, false);
	free_tree_node(comp_tree);
	
	comp_tree = new_tree_node(new_leaf(new_parameter("x")), new_function(&sub), new_leaf(new_constant(5.0)));
	print_tree(comp_tree);
	result = evaluate(comp_tree, NULL);	
	test_equal_b(result.valid, false);
	free_tree_node(comp_tree);
	
	comp_tree = new_tree_node(new_leaf(new_parameter("x")), new_function(&mul), new_leaf(new_constant(5.0)));
	print_tree(comp_tree);
	result = evaluate(comp_tree, parameter_list);	
	test_within_d(result.result, 10.0, 1.0e-6);
	test_equal_b(result.valid, true);
	free_tree_node(comp_tree);
	
	comp_tree = new_tree_node(new_leaf(new_parameter("z")), new_function(&add), NULL);
	print_tree(comp_tree);
	result = evaluate(comp_tree, parameter_list);	
	test_equal_b(result.valid, false);
	free_tree_node(comp_tree);
	
	comp_tree = new_tree_node(NULL, new_function(&divi), new_leaf(new_parameter("y")));
	print_tree(comp_tree);
	result = evaluate(comp_tree, parameter_list);	
	test_equal_b(result.valid, false);
	free_tree_node(comp_tree);
	
	
	comp_tree = new_tree_node(new_tree_node(new_leaf(new_parameter("x")), new_function(&add), new_leaf(new_parameter("x"))), new_function(&mul), new_leaf(new_constant(-2.0)));
	print_tree(comp_tree);
	result = evaluate(comp_tree, parameter_list);	
	test_within_d(result.result, -8.0, 1.0e-6);
	test_equal_b(result.valid, true);
	free_tree_node(comp_tree);
	
	comp_tree = new_tree_node(new_leaf(new_constant(4.0)), new_function(&divi), new_tree_node(new_leaf(new_parameter("z")), new_function(&mul), new_leaf(new_parameter("z"))));
	print_tree(comp_tree);
	result = evaluate(comp_tree, parameter_list);	
	test_within_d(result.result, 0.197531, 1.0e-6);
	test_equal_b(result.valid, true);
	free_tree_node(comp_tree);
	
	comp_tree = new_tree_node(new_leaf(new_constant(4.0)), new_function(&divi), new_tree_node(new_leaf(new_parameter("g")), new_function(&mul), new_leaf(new_parameter("z"))));
	print_tree(comp_tree);
	result = evaluate(comp_tree, parameter_list);	
	test_equal_b(result.valid, false);
	free_tree_node(comp_tree);
	
	parameter_list = new_pnode("m", 2, new_pnode("b", 3, parameter_list));
	
	
	comp_tree = new_tree_node(new_leaf(new_parameter("b")), new_function(&add), new_tree_node(new_leaf(new_parameter("m")), new_function(&mul), new_leaf(new_parameter("x"))));
	print_tree(comp_tree);
	result = evaluate(comp_tree, parameter_list);	
	test_within_d(result.result, 7.0, 1.0e-6);
	test_equal_b(result.valid, true);
	free_tree_node(comp_tree);
	
	comp_tree = new_tree_node(new_leaf(new_constant(1.0)), new_function(&add), new_tree_node(new_tree_node(new_leaf(new_constant(-3.0)), new_function(&mul), new_leaf(new_parameter("y"))) , new_function(&add) , new_tree_node(new_tree_node(new_leaf(new_parameter("x")), new_function(&mul), new_leaf(new_parameter("x"))), new_function(&mul), new_leaf(new_constant(2.0)))));
	print_tree(comp_tree);
	result = evaluate(comp_tree, parameter_list);	
	test_within_d(result.result, 0.0, 1.0e-6);
	test_equal_b(result.valid, true);
	free_tree_node(comp_tree);
	
	free_pnode(parameter_list);	
}

//precomputes the tree
TreeNode* precompute_tree(TreeNode* tree){
	//todo:
	
	TreeNode* t = NULL;

	return t;
}

void test_precompute(){
	printf("-------------------------\n");
	printf("Test precompute function:\n");
	printf("-------------------------\n");
	
	test_equal_b(tree_equals_tree(precompute_tree(NULL), NULL), true);
	
	TreeNode* comp_tree = NULL;
	TreeNode* precomputed = NULL;
	TreeNode* expected = NULL;
	
	printf("Tree:\n");
	comp_tree = new_leaf(new_constant(3.0));
	print_tree(comp_tree);
	printf("Precomputed tree:\n");
	precomputed = precompute_tree(comp_tree);
	print_tree(precomputed);
	printf("Expected precomputed tree:\n");
	expected = new_leaf(new_constant(3.0));
	print_tree(expected);
	test_equal_b(tree_equals_tree(precomputed, expected), true);
	
	free_tree_node(comp_tree);
	free_tree_node(precomputed);
	free_tree_node(expected);
	
	printf("Tree:\n");
	comp_tree = new_leaf(new_parameter("c"));
	print_tree(comp_tree);
	printf("Precomputed tree:\n");
	precomputed = precompute_tree(comp_tree);
	print_tree(precomputed);
	printf("Expected precomputed tree:\n");
	expected = new_leaf(new_parameter("c"));
	print_tree(expected);
	test_equal_b(tree_equals_tree(precomputed, expected), true);
	
	free_tree_node(comp_tree);
	free_tree_node(precomputed);
	free_tree_node(expected);
	

	printf("Tree:\n");
	comp_tree = new_tree_node(new_leaf(new_constant(1.0)), new_function(&add), new_leaf(new_constant(-3.0)));
	print_tree(comp_tree);
	printf("Precomputed tree:\n");
	precomputed = precompute_tree(comp_tree);
	print_tree(precomputed);
	printf("Expected precomputed tree:\n");
	expected = new_leaf(new_constant(-2.0));
	print_tree(expected);
	test_equal_b(tree_equals_tree(precomputed, expected), true);
	
	free_tree_node(comp_tree);
	free_tree_node(precomputed);
	free_tree_node(expected);
	
	printf("Tree:\n");
	comp_tree = new_tree_node(new_leaf(new_parameter("x")), new_function(&add), new_leaf(new_constant(0.0)));
	print_tree(comp_tree);
	printf("Precomputed tree:\n");
	precomputed = precompute_tree(comp_tree);
	print_tree(precomputed);
	printf("Expected precomputed tree:\n");
	expected = new_leaf(new_parameter("x"));
	print_tree(expected);
	test_equal_b(tree_equals_tree(precomputed, expected), true);
	
	free_tree_node(comp_tree);
	free_tree_node(precomputed);
	free_tree_node(expected);
	
	printf("Tree:\n");
	comp_tree = new_tree_node(new_leaf(new_parameter("x")), new_function(&add), new_leaf(new_constant(1.0)));
	print_tree(comp_tree);
	printf("Precomputed tree:\n");
	precomputed = precompute_tree(comp_tree);
	print_tree(precomputed);
	printf("Expected precomputed tree:\n");
	expected = new_tree_node(new_leaf(new_parameter("x")), new_function(&add), new_leaf(new_constant(1.0)));
	print_tree(expected);
	test_equal_b(tree_equals_tree(precomputed, expected), true);
	
	free_tree_node(comp_tree);
	free_tree_node(precomputed);
	free_tree_node(expected);
	
	printf("Tree:\n");
	comp_tree = new_tree_node(new_leaf(new_constant(1.0)), new_function(&mul), new_leaf(new_parameter("y")));
	print_tree(comp_tree);
	printf("Precomputed tree:\n");
	precomputed = precompute_tree(comp_tree);
	print_tree(precomputed);
	printf("Expected precomputed tree:\n");
	expected = new_leaf(new_parameter("y"));
	print_tree(expected);
	test_equal_b(tree_equals_tree(precomputed, expected), true);
	
	free_tree_node(comp_tree);
	free_tree_node(precomputed);
	free_tree_node(expected);
	
	printf("Tree:\n");
	comp_tree = new_tree_node(new_leaf(new_constant(0.0)), new_function(&divi), new_leaf(new_parameter("z")));
	print_tree(comp_tree);
	printf("Precomputed tree:\n");
	precomputed = precompute_tree(comp_tree);
	print_tree(precomputed);
	printf("Expected precomputed tree:\n");
	expected = new_leaf(new_constant(0.0));
	print_tree(expected);
	test_equal_b(tree_equals_tree(precomputed, expected), true);
	
	free_tree_node(comp_tree);
	free_tree_node(precomputed);
	free_tree_node(expected);
	
	printf("Tree:\n");
	comp_tree = new_tree_node(new_leaf(new_parameter("z")), new_function(&divi), new_leaf(new_constant(1.0)));
	print_tree(comp_tree);
	printf("Precomputed tree:\n");
	precomputed = precompute_tree(comp_tree);
	print_tree(precomputed);
	printf("Expected precomputed tree:\n");
	expected = new_leaf(new_parameter("z"));
	print_tree(expected);
	test_equal_b(tree_equals_tree(precomputed, expected), true);
	
	free_tree_node(comp_tree);
	free_tree_node(precomputed);
	free_tree_node(expected);
	
	printf("Tree:\n");
	comp_tree = new_tree_node(new_leaf(new_constant(0.0)), new_function(&add), new_leaf(new_parameter("b")));
	print_tree(comp_tree);
	printf("Precomputed tree:\n");
	precomputed = precompute_tree(comp_tree);
	print_tree(precomputed);
	printf("Expected precomputed tree:\n");
	expected = new_leaf(new_parameter("b"));
	print_tree(expected);
	test_equal_b(tree_equals_tree(precomputed, expected), true);
	
	free_tree_node(comp_tree);
	free_tree_node(precomputed);
	free_tree_node(expected);
	
	printf("Tree:\n");
	comp_tree = new_tree_node(new_leaf(new_parameter("b")), new_function(&sub), new_leaf(new_parameter("b")));
	print_tree(comp_tree);
	printf("Precomputed tree:\n");
	precomputed = precompute_tree(comp_tree);
	print_tree(precomputed);
	printf("Expected precomputed tree:\n");
	expected = new_leaf(new_constant(0.0));
	print_tree(expected);
	test_equal_b(tree_equals_tree(precomputed, expected), true);
	
	free_tree_node(comp_tree);
	free_tree_node(precomputed);
	free_tree_node(expected);
	
	printf("Tree:\n");
		comp_tree = new_tree_node(new_tree_node(new_leaf(new_constant(0.0)), new_function(&add), new_leaf(new_constant(3.0))), new_function(&add), new_tree_node(new_leaf(new_parameter("x")), new_function(&mul), new_leaf(new_constant(0.0))));
	comp_tree = new_tree_node(comp_tree, new_function(&mul), new_tree_node(new_leaf(new_parameter("z")), new_function(&divi) , new_tree_node(new_leaf(new_parameter("z")), new_function(&sub) , new_leaf(new_constant(0)))));
	print_tree(comp_tree);
	printf("Precomputed tree:\n");
	precomputed = precompute_tree(comp_tree);
	print_tree(precomputed);
	printf("Expected precomputed tree:\n");
	expected = new_leaf(new_constant(3.0));
	print_tree(expected);
	test_equal_b(tree_equals_tree(precomputed, expected), true);
	
	free_tree_node(comp_tree);
	free_tree_node(precomputed);
	free_tree_node(expected);
}

int main(void){
	report_memory_leaks(true);
	
	test_evaluate();
	test_precompute();

	return 0;
}
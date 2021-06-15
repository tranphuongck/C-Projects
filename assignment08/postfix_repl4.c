/*
	make postfix_repl && ./postfix_repl
*/

#include "base.h"

/*
    Macro for testing if a condition is valid for all i's in the range of [0, length)].
    e.g.
    int length = 10;
    int x[length];
    
    ensure("Array initialized with 0's", forall_i(length, x[i] == 0));

*/
#define forall_i(length, condition) ({\
   bool result = true;\
   for (int i = 0; i < length; i++) { if (!(condition)) { result = false; break; } }\
   result;\
})


#define STACK_SIZE  10

typedef enum {
	OPERATION, VALUE, EMPTY
} Tag;



typedef struct{
	Tag tag;
	
	union{
		int value;
		char operation;
	};
} StackElement;

typedef struct{
	StackElement elements[STACK_SIZE];
	int stack_pointer;
    int stack_height;
} Stack;

//checks if char c belongs to an operation
bool is_operation(char c){
	return c == '+' || c == '/' || c == '-' || c == '*';
}

//checks wheter c is a digit
bool is_digit(char c){
	return c >= '0' && c <= '9';
}

//todo:
StackElement make_stack_element(Tag tag){
	StackElement ele;
	ele.tag = tag;
	return ele;
} 
//todo:
StackElement make_value(int value){
	StackElement ele;
	ele = make_stack_element(VALUE);
	ele.value = value;
	return ele;
}
//todo:
StackElement make_operation(char operation){
	StackElement ele;  
	ele = make_stack_element(OPERATION);
	ele.operation = operation;
	return ele;
}

bool is_empty(Stack* stack){
	return stack->stack_pointer < 0;
}

//todo:
void clear_stack(Stack* stack){
	//todo
	require("non empty stack",stack !=NULL);
	stack->stack_pointer = -1 ;
	for(int i = 0; i < STACK_SIZE; i++){
		stack->elements[i] = make_stack_element(EMPTY);
	}
	forall_i(STACK_SIZE,stack->elements[i].tag == EMPTY);
}

void push(StackElement element, Stack* stack){
    require_not_null(stack);
	if(stack->stack_pointer < (stack->stack_height - 1)){
		stack->stack_pointer++;
		stack->elements[stack->stack_pointer] = element;
	}
}

StackElement pop(Stack* stack){
    require_not_null(stack);
    require("non empty stack", stack->stack_pointer >= 0);
    StackElement ele = stack->elements[stack->stack_pointer ];
    stack->elements[stack->stack_pointer] = make_stack_element(EMPTY);
	stack->stack_pointer--;
	return ele;
}

//todo:
void print_stack_element(StackElement ele){
	//todo
	switch (ele.tag) {
	case EMPTY:
		printf("[]\n");
		break;
	case OPERATION:
		printf("[%c]\n", ele.operation);
		break;
	case VALUE:
		printf("[%i]\n", ele.value);
		break;
	}
}

//todo:
void print_stack(Stack* stack, int n){
	//todo:
	require("valid n", n <= STACK_SIZE);
	require("valid n", n >= 0 );
	for (int i = n - 1; i >= 0; i--){
		print_stack_element(stack->elements[i]);
		println();
	}
}

void compute(Stack* stack){
	//todo
 	require("stack not empty", stack !=NULL);
 	require("valid operation", stack->stack_height >= 3);

	if(stack->elements[stack->stack_pointer].tag == OPERATION){
		StackElement op = pop(stack)  ;
		int a;
		switch (op.operation) {
		case '+':
			a = pop(stack).value + pop(stack).value;
			break;
		case '-':
			a = pop(stack).value - pop(stack).value;
			break;
		case '*':
		 	a = pop(stack).value * pop(stack).value;
			break;
		case '/':
		 	a = pop(stack).value / pop(stack).value;
			break;
		}
		push(make_value(a),stack);
	}
	ensure("valid value",stack->elements[stack->stack_pointer].tag == VALUE);
}


int main (void){	
	Stack stack;
    stack.stack_height = STACK_SIZE;
	clear_stack(&stack);
	

	int input_size = 128;	
	char input[input_size];
	
	for(int i = 0; i< input_size; i++){
		input[i] = '\0';
	}
	int input_index = 0;
	
	print_stack(&stack,STACK_SIZE);
	int c;
	while((c = getchar()) != 'q'){

		if(c == '\n'){
			for(int i = 0; i< input_index; i++){
                char c = input[i];
				//todo:
				if (is_operation(c)){
					push(make_operation(c),&stack);
					print_stack(&stack,STACK_SIZE);
					compute(&stack);
				} else if (is_digit(c)){
					int i = c - '0';
					push(make_value(i),&stack);
					}
				print_stack(&stack,STACK_SIZE);
			}
			
			for(int i = 0; i< input_size; i++){
				input[i] = '\0';
			}
			input_index = 0;
			
		}else{
			input[input_index] = c;
			input_index++;
		}

	
	}
	return 0;
}
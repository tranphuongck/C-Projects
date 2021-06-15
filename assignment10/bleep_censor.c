/*
    make bleep_censor
    ./bleep_censor
    make bleep_censor && ./bleep_censor

*/

#include "base.h"



typedef struct Token{
    char* start;
    char* end;
}Token;

typedef struct TreeNode{
    struct TreeNode* left;
    struct TreeNode* right;
    Token* token;
}TreeNode;

Token* new_token(char* start, char* end){
    Token* t = xmalloc(sizeof(Token));
    t->start = start;
    t->end = end;
    return t;
}

void print_token(Token* t, bool censored) {
    //todo

}

void print_tokenln(Token* t, bool censored) {
    print_token(t, censored);
    printc('\n');
}

TreeNode* new_tree_node(TreeNode* left, Token* token, TreeNode* right){
    TreeNode* tree_node = xmalloc(sizeof(TreeNode));
    tree_node->token = token;
    tree_node->left = left;
    tree_node->right = right;
    return tree_node;
}

void free_tree(TreeNode* tree){
    //todo

}

TreeNode* new_leaf(Token* token){
    return new_tree_node(NULL, token, NULL);
}

void print_tree(TreeNode* tree){
    if(tree == NULL){
        return;
    }
    print_tree(tree->left);
    printc(' ');
    print_token(tree->token, false);
    printc(' ');
    print_tree(tree->right);
}

int compare_token(Token* t1, Token* t2){
    //todo
   
    
    return 0;
    
}

void test_token_compare(){
    char* s = "hallo huhu hall HALLO";
    
    Token hallo = {s + 0, s + 5};
    //print_tokenln(&hallo);
    Token huhu = {s + 6, s + 10};
    //print_tokenln(&huhu);
    Token hall = {s + 11, s + 15};
    //print_tokenln(&hall);
    Token hallo_2 = {s + 16, s + 21};
    //print_tokenln(&hallo_2);
    
    test_equal_i(compare_token(&hallo, &hallo), 0);
    test_equal_i(compare_token(&huhu, &huhu), 0);
    test_equal_i(compare_token(&huhu, &hallo), 1);
    test_equal_i(compare_token(&hallo, &huhu), -1);
    test_equal_i(compare_token(&hall, &hallo), -1);
    test_equal_i(compare_token(&hallo, &hall), 1);
    test_equal_i(compare_token(&hallo, &hallo_2), 0);
    test_equal_i(compare_token(&hallo_2, &hallo), 0);
    
}

bool contains(TreeNode* tree, Token* token){
    if(tree == NULL){
        return false;
    }
    
    int cmp_result = compare_token(token, tree->token);
    if(cmp_result == 0){
        return true;
    }
    else if(cmp_result < 0){
        return contains(tree->left, token);
    }else{
        return contains(tree->right, token);
    }  
}



void insert_in_tree(TreeNode** tree, Token* token){
    //todo

}

void test_insert_token(){
    char* s = "hallo huhu hall HALLO";
    
    Token hallo = {s + 0, s + 5};
    //print_tokenln(&hallo);
    Token huhu = {s + 6, s + 10};
    //print_tokenln(&huhu);
    Token hall = {s + 11, s + 15};
    //print_tokenln(&hall);
    
    TreeNode* tree = NULL;
    
    insert_in_tree(&tree, &hallo);
    
    test_equal_i(compare_token(tree->token, &hallo), 0);
    
    insert_in_tree(&tree, &hallo);
    test_equal_i(compare_token(tree->token, &hallo), 0);
    
    insert_in_tree(&tree, &hall);
    test_equal_i(compare_token(tree->left->token, &hall), 0);
    
    insert_in_tree(&tree, &huhu);
    test_equal_i(compare_token(tree->right->token, &huhu), 0);
    
    free(tree->left);
    free(tree->right);
    free(tree);
    
}


TreeNode* create_bleep_tree(char* bleep_words){
    //todo
        
    return NULL;
}

void test_create_bleep_tree(){
    char* s = "hallo huhu hall HALLO";
    // int i = 0;
    // while i != ' ' -> i++;

    Token hallo = {s + 0, s + 5};
    //print_tokenln(&hallo);
    Token huhu = {s + 6, s + 10};
    //print_tokenln(&huhu);
    Token hall = {s + 11, s + 15};
    //print_tokenln(&hall);
    
    TreeNode* tree = create_bleep_tree(s);
   
    test_equal_i(compare_token(tree->token, &hallo), 0);  
    test_equal_i(compare_token(tree->left->token, &hall), 0); 
    test_equal_i(compare_token(tree->right->token, &huhu), 0);
    
    free_tree(tree);
}

int main(void){    
    //report_memory_leaks(true);
    //test_token_compare();
    //test_insert_token(); <--- uncomment when implemented
    //test_create_bleep_tree(); <--- uncomment when implemented
    /*
    char* bleep_words = "schwein affe dumm bloed bloedmann idiot ";    
    TreeNode* tree = create_bleep_tree(bleep_words);
    
    print_tree(tree);
    printc('\n');
    
    char buffer[256];
    get_line(buffer, 256);
    printf("Original String: %s\n", buffer);
    
    printf("Bleeped String:\n", buffer);
    //todo


    
    free_tree(tree);
    */
    char* s = "abc def ghi";
    printf("%s \n", s);
    s = s + 4;
    printf("%s \n", s);
    return 0;
}
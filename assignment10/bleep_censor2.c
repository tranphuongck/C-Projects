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
    int length = t->end - t->start;
    if(censored == true){ //skip the 1st character, print * for each of the remaining characters
        printf("%c",t->start[0]);
        for (int i = 0; i < length - 1; i++) printf("*");
        printf(" ");
    } else {
        for (int i = 0; i < length; i++) printf("%c",t->start[i]);
        printf(" ");
    }
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
    if(tree == NULL) return;
    else {
        free(tree->token);
        free_tree(tree->left);
        free_tree(tree->right);
        free(tree);
    }
}

TreeNode* new_leaf(Token* token){
    return new_tree_node(NULL, token, NULL);
}

void print_tree(TreeNode* tree){
    if(tree == NULL) return;
    print_tree(tree->left);
    printf(" ");
    print_token(tree->token, false);
    printf(" ");
    print_tree(tree->right);
}

int compare_token(Token* t1, Token* t2) {
    //todo
    int i = 0;
    while (i <= t1->end - t1->start || i <= t2->end - t2->start){
        //Use toupper() to convert between lowercase and uppercase characters
        if(toupper(t1->start[i]) < toupper(t2->start[i]) && t1->start[i] != 0 && t2->start[i] != 0) return -1;
        else if(toupper(t1->start[i]) > toupper(t2->start[i]) && t1->start[i] != 0 && t2->start[i] != 0) return 1;
        i++;
    }
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
    TreeNode* temptree = NULL;
    if((*tree) == NULL) { //if tree is empty, insert the token as root
        temptree = new_leaf(token);
        *tree = temptree;
        return;
    } else {
        if (compare_token((*tree)->token,token) > 0 ){ //else, recursively insert new tokens in tree
        insert_in_tree(&(*tree)->left,token);
        } else if (compare_token(((*tree)->token),token) < 0){
            insert_in_tree(&(*tree)->right,token);
        }
    } 
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
    TreeNode* tree = NULL;
    if (bleep_words == NULL) return tree; 
    int j = 0;
    for(int i = 0; i < strlen(bleep_words); i++){
        while (bleep_words[i] != ' ' ) i++;
        Token* token = new_token(bleep_words + j, bleep_words + i); //generate token from words
        insert_in_tree(&tree,token); //insert new tokens in tree
        j = i + 1;
        i++;
    }
    return tree;
}

void test_create_bleep_tree(){
    char* s = "hallo huhu hall HALLlO ";
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
    report_memory_leaks(true);
    test_token_compare();
    test_insert_token(); 
    test_create_bleep_tree();
    
    char* bleep_words = "schwein affe dumm bloed bloedmann idiot ";    
    TreeNode* tree = create_bleep_tree(bleep_words);
    
    print_tree(tree);
    printc('\n');
    
    char buffer[256];
    get_line(buffer, 256);

    printf("Original String: %s\n", buffer);
    printf("Bleeped String: ", buffer);
    //todo
    int j = 0;
    for(int i = 0 ; i < strlen(buffer); i++){
        while (buffer[i] != ' ' ) i++;
        Token* token = new_token(buffer + j,buffer + i);
        bool value = contains(tree,token);
        print_token(token,value);
        free(token);
        j = i + 1 ;
        i++;
    }
    println();
    free_tree(tree);
    return 0;
}
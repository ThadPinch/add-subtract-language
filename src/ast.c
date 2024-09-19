// ast.c
#include <stdlib.h>
#include "ast.h"

ASTNode* create_number_node(int value) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = AST_NUMBER;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

ASTNode* create_binary_node(ASTNodeType type, ASTNode *left, ASTNode *right) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = type;
    node->left = left;
    node->right = right;
    node->value = 0;
    return node;
}

ASTNode* create_print_node(ASTNode *expr) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = AST_PRINT;
    node->left = expr;
    node->right = NULL;
    node->value = 0;
    return node;
}

void free_ast(ASTNode *node) {
    if (node == NULL) return;
    free_ast(node->left);
    free_ast(node->right);
    free(node);
}

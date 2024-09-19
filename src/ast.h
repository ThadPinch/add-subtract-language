// ast.h
#ifndef AST_H
#define AST_H

typedef enum {
    AST_PRINT,
    AST_ADD,
    AST_SUBTRACT,
    AST_NUMBER
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    struct ASTNode *left;
    struct ASTNode *right;
    int value; // Only used for AST_NUMBER
} ASTNode;

// Function to create AST nodes
ASTNode* create_number_node(int value);
ASTNode* create_binary_node(ASTNodeType type, ASTNode *left, ASTNode *right);
ASTNode* create_print_node(ASTNode *expr);

// Function to free AST
void free_ast(ASTNode *node);

#endif // AST_H

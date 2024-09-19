// codegen.c
#include <stdio.h>
#include "codegen.h"

void generate_expression(ASTNode *node, FILE *output) {
    if (node->type == AST_NUMBER) {
        fprintf(output, "%d", node->value);
    } else if (node->type == AST_ADD) {
        fprintf(output, "(");
        generate_expression(node->left, output);
        fprintf(output, " + ");
        generate_expression(node->right, output);
        fprintf(output, ")");
    } else if (node->type == AST_SUBTRACT) {
        fprintf(output, "(");
        generate_expression(node->left, output);
        fprintf(output, " - ");
        generate_expression(node->right, output);
        fprintf(output, ")");
    }
}

void generate_code(ASTNode *node, FILE *output) {
    if (node == NULL) return;

    if (node->type == AST_PRINT) {
        fprintf(output, "    printf(\"%%d\\n\", ");
        generate_expression(node->left, output);
        fprintf(output, ");\n");
    }

    // Handle multiple statements if needed
    if (node->right != NULL) {
        generate_code(node->right, output);
    }
}

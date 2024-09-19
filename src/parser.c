// parser.c

#include <stdio.h>
#include <stdlib.h> // Ensure this is included for 'exit'
#include "parser.h"
#include "ast.h"

// Forward declarations
ASTNode* parse_statement(Parser *parser);
ASTNode* parse_expression(Parser *parser);
ASTNode* parse_term(Parser *parser);

void init_parser(Parser *parser, const char *source) {
    init_lexer(&parser->lexer, source);
    parser->current_token = get_next_token(&parser->lexer);
}

void error(const char *message, int line) {
    fprintf(stderr, "Error (line %d): %s\n", line, message);
    exit(1);
}

void eat(Parser *parser, TokenType type) {
    if (parser->current_token.type == type) {
        parser->current_token = get_next_token(&parser->lexer);
    } else {
        error("Unexpected token", parser->current_token.line);
    }
}

ASTNode* parse_program(Parser *parser) {
    ASTNode *root = NULL;
    ASTNode *current = NULL;

    while (parser->current_token.type != TOKEN_EOF) {
        ASTNode *stmt = parse_statement(parser);
        if (root == NULL) {
            root = stmt;
            current = root;
        } else {
            current->right = stmt;
            current = stmt;
        }
    }

    return root;
}

ASTNode* parse_statement(Parser *parser) {
    if (parser->current_token.type == TOKEN_PRINT) {
        eat(parser, TOKEN_PRINT);
        ASTNode *expr = parse_expression(parser);
        if (parser->current_token.type != TOKEN_SEMICOLON) {
            error("Expected ';' at end of statement", parser->current_token.line);
        }
        eat(parser, TOKEN_SEMICOLON);
        return create_print_node(expr);
    } else {
        error("Expected 'print' statement", parser->current_token.line);
        return NULL;
    }
}

ASTNode* parse_expression(Parser *parser) {
    ASTNode *node = parse_term(parser);

    while (parser->current_token.type == TOKEN_PLUS ||
           parser->current_token.type == TOKEN_MINUS) {
        TokenType op = parser->current_token.type;
        if (op == TOKEN_PLUS) {
            eat(parser, TOKEN_PLUS);
            ASTNode *right = parse_term(parser);
            node = create_binary_node(AST_ADD, node, right);
        } else if (op == TOKEN_MINUS) {
            eat(parser, TOKEN_MINUS);
            ASTNode *right = parse_term(parser);
            node = create_binary_node(AST_SUBTRACT, node, right);
        }
    }

    return node;
}

ASTNode* parse_term(Parser *parser) {
    if (parser->current_token.type == TOKEN_NUMBER) {
        int value = parser->current_token.value;
        eat(parser, TOKEN_NUMBER);
        return create_number_node(value);
    } else {
        error("Expected number in expression", parser->current_token.line);
        return NULL;
    }
}

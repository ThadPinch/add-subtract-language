// parser.h
#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"

typedef struct {
    Lexer lexer;
    Token current_token;
} Parser;

void init_parser(Parser *parser, const char *source);
ASTNode* parse_program(Parser *parser);

#endif // PARSER_H

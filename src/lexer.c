#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h> 
#include "lexer.h"

void init_lexer(Lexer *lexer, const char *source) {
    lexer->source = source;
    lexer->pos = 0;
    lexer->line = 1;
}

Token get_next_token(Lexer *lexer) {
    Token token;
    token.value = 0;
    token.line = lexer->line;

    while (lexer->source[lexer->pos] != '\0') {
        char current = lexer->source[lexer->pos];

        // Skip whitespace
        if (isspace(current)) {
            if (current == '\n') {
                lexer->line++;
            }
            lexer->pos++;
            continue;
        }

        // Handle 'print' keyword
        if (isalpha(current)) {
            size_t start = lexer->pos;
            while (isalnum(lexer->source[lexer->pos])) {
                lexer->pos++;
            }
            size_t length = lexer->pos - start;
            char word[20];
            if (length >= sizeof(word)) {
                length = sizeof(word) - 1;
            }
            strncpy(word, &lexer->source[start], length);
            word[length] = '\0';

            if (strcmp(word, "print") == 0) {
                token.type = TOKEN_PRINT;
                return token;
            } else {
                token.type = TOKEN_INVALID;
				if (token.type == TOKEN_INVALID) {
					fprintf(stderr, "Error (line %d): Invalid token '%c'\n", lexer->line, current);
					exit(1);
				}
                return token;
            }
        }

        // Handle numbers
        if (isdigit(current)) {
            int number = 0;
            while (isdigit(lexer->source[lexer->pos])) {
                number = number * 10 + (lexer->source[lexer->pos] - '0');
                lexer->pos++;
            }
            token.type = TOKEN_NUMBER;
            token.value = number;
            return token;
        }

        // Handle operators and punctuation
        switch (current) {
            case '+':
                token.type = TOKEN_PLUS;
                lexer->pos++;
                return token;
            case '-':
                token.type = TOKEN_MINUS;
                lexer->pos++;
                return token;
            case ';':
                token.type = TOKEN_SEMICOLON;
                lexer->pos++;
                return token;
            default:
                token.type = TOKEN_INVALID;
                lexer->pos++;
                return token;
        }
    }

    token.type = TOKEN_EOF;
    return token;
}

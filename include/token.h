//token.h
#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_PRINT,
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_SEMICOLON,
    TOKEN_EOF,
    TOKEN_INVALID
} TokenType;

typedef struct {
    TokenType type;
    int value;      // Only used for TOKEN_NUMBER
    int line;       // Line number for error reporting
} Token;	

#endif
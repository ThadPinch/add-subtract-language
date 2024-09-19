#ifndef LEXER_H
#define LEXER_H

#include "token.h"

typedef struct { 
	const char *source;
	int pos;
	int line;
} Lexer;

void init_lexer(Lexer *lexer, const char *source);
Token get_next_token(Lexer *lexer);

#endif
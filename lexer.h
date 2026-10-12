#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

typedef enum {
    TOK_ATOM,
    TOK_OP,
    TOK_EOF
} token_type_t;

typedef struct {
    token_type_t type;
    union {
        char chr;
    } data;
} token_t;

typedef struct {
    int len;
    int cap;
    token_t *toks;
} lexer_t;

lexer_t lexer_new(char *input, int len);

token_t lexer_next(lexer_t *l);
token_t lexer_peek(lexer_t *l);

#endif // LEXER_H
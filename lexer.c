#include "lexer.h"
#include <ctype.h>
#include <stdlib.h>

const int DEFAULT_SIZE = 100;

static void lexer_tokenize(lexer_t *l, char *input, int len);
static void lexer_push(lexer_t *l, token_t t);
static void lexer_trim(lexer_t *l);

lexer_t lexer_new(char *input, int len) {
    lexer_t l = {0};
    l.len = 0;
    l.cap = DEFAULT_SIZE;
    l.toks = malloc(DEFAULT_SIZE * sizeof(token_t));
    
    lexer_tokenize(&l, input, len);
    lexer_trim(&l);

    return l;
}

token_t lexer_next(lexer_t *l) {
    if (l->len == 0) return (token_t){.type = TOK_EOF};
    token_t t = l->toks[--l->len];
    return t;
}

token_t lexer_peek(lexer_t *l) {
    if (l->len == 0) return (token_t){.type = TOK_EOF};
    token_t t = l->toks[l->len-1];
    return t;
}

static void lexer_tokenize(lexer_t *l, char *input, int len) {
    for (int i = len-1; i >= 0; i--) {
        if (isspace(input[i])) {
            continue;
        }

        if (isalnum(input[i])) {
            lexer_push(l, (token_t){.type = TOK_ATOM, .data.chr = input[i]});
        } else {
            lexer_push(l, (token_t){.type = TOK_OP, .data.chr = input[i]});
        }
    }
}

static void lexer_trim(lexer_t *l) {
    l->toks = realloc(l->toks, l->len * sizeof(token_t));
    l->cap = l->len;
}

static void lexer_push(lexer_t *l, token_t t) {
    if (l->cap == l->len) {
        l->cap += 10;
        l->toks = realloc(l->toks, l->cap * sizeof(token_t));
    }
    
    l->toks[l->len] = t;
    l->len++;
}
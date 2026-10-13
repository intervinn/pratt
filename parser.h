#ifndef PARSER_H
#define PARSER_H

#include "s.h"
#include "lexer.h"

typedef struct {
    int l;
    int r;
} pair_t;

s_t expr(char *input);
s_t expr_bp(lexer_t *l, int min_bp);
pair_t infix_binding_power(char op);
int prefix_binding_power(char op);



#endif // PARSER_H
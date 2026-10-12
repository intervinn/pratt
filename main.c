#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "lexer.h"
#include "s.h"

typedef struct {
    int l;
    int r;
} pair_t;

s_t expr(char *input);
s_t expr_bp(lexer_t *l, int min_bp);
pair_t infix_binding_power(char op);
int prefix_binding_power(char op);

int prefix_binding_power(char op) {
    switch (op) {
        case '+':
        case '-':
        return 5;

        default:
        printf("bad op: %c\n", op);
        return 0;
    }
}

pair_t infix_binding_power(char op) {
    switch (op) {
        case '+':
        case '-':
        return (pair_t){1, 2};

        case '*':
        case '/':
        return (pair_t){3, 4};
        
        case '.':
        return (pair_t){8, 7};

        default:
        printf("bad op: %c\n", op);
        return (pair_t){0, 0};
    }
}

s_t expr(char *input) {
    lexer_t lexer = lexer_new(input, strlen(input));
    return expr_bp(&lexer, 0);
}

s_t expr_bp(lexer_t *l, int min_bp) {
    s_t lhs = {0};
    token_t next = lexer_next(l);
    switch (next.type) {
        case TOK_ATOM:
            lhs.type = S_ATOM;
            lhs.data.atom.chr = next.data.chr;
            break;
        case TOK_OP: {
            int bp = prefix_binding_power(next.data.chr);
            s_t rhs = expr_bp(l, bp);
            lhs.type = S_CONS;
            lhs.data.cons.cap = 1;
            lhs.data.cons.len = 1;
            lhs.data.cons.op = next.data.chr;
            lhs.data.cons.inner = malloc(lhs.data.cons.len * sizeof(s_t));
            lhs.data.cons.inner[0] = rhs;
            break;
        }
        default:
            printf("lhs: bad token: %c\n", next.data.chr);
            return lhs;
    }

    while (true) {
        token_t op = lexer_peek(l);
        if (op.type == TOK_EOF) break;
        if (op.type != TOK_OP) {
            printf("op: bad token: %c\n", op.data.chr);
            return lhs;
        }

        pair_t bp = infix_binding_power(op.data.chr);
        if (bp.l < min_bp) break;
        lexer_next(l);
        s_t rhs = expr_bp(l, bp.r);

        s_t old_lhs = lhs;
        lhs.type = S_CONS;
        lhs.data.cons.cap = 2;
        lhs.data.cons.len = 2;
        lhs.data.cons.op = op.data.chr;
        lhs.data.cons.inner = malloc(lhs.data.cons.len * sizeof(s_t));
        lhs.data.cons.inner[0] = old_lhs;
        lhs.data.cons.inner[1] = rhs;
    }

    return lhs;
}

int main() {
    s_fmt(expr("1"), stdout); puts("\n");
    s_fmt(expr("1 + 2 * 3"), stdout); puts("\n");
    s_fmt(expr("a * b * c *d + e"), stdout); puts("\n");
    s_fmt(expr("f . g . h"), stdout); puts("\n");
    s_fmt(expr("1 + 2 + f . g . h * 3 * 4"), stdout); puts("\n");
    s_fmt(expr("2 + 2 * 2"), stdout); puts("\n");
    s_fmt(expr("-1 * 2"), stdout); puts("\n");

    return 0;
}
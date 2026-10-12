#ifndef S_H
#define S_H

#include <stdio.h>

typedef enum {
    S_BAD,
    S_ATOM,
    S_CONS
} s_type_t;

typedef struct s_t {
    s_type_t type;
    union {
        struct {
            char chr;
        } atom;

        struct {
            struct s_t *inner;
            int len;
            int cap;
            char op;
        } cons;
    } data;
} s_t;

void s_fmt(s_t s, FILE *f);

#endif // S_H
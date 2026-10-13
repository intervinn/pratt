#include "s.h"

void s_fmt(s_t s, FILE *f) {
    switch (s.type) {
        case S_ATOM: fputc(s.data.atom.chr, f); break;
        case S_CONS: {
            if (s.data.cons.len == 0) return;

            fputc('(', f);
            fputc(s.data.cons.op, f);

            if (s.data.cons.len == 0) {
                fputc(')', f);
                return;
            }

            for (int i = 0; i < s.data.cons.len; i++) {
                fputc(' ', f);
                s_fmt(s.data.cons.inner[i], f);
            }
            fputc(')', f);

            break;
        }
        case S_BAD:
            fprintf(f, "<bad>");
            break;
    }
}
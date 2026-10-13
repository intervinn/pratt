#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "parser.h"
#include "s.h"

int main() {
    s_fmt(expr("1"), stdout); puts("\n");
    s_fmt(expr("1 + 2 * 3"), stdout); puts("\n");
    s_fmt(expr("a * b * c *d + e"), stdout); puts("\n");
    s_fmt(expr("f . g . h"), stdout); puts("\n");
    s_fmt(expr("1 + 2 + f . g . h * 3 * 4"), stdout); puts("\n");
    s_fmt(expr("2 + 2 * 2"), stdout); puts("\n");
    s_fmt(expr("--1 * 2"), stdout); puts("\n");

    return 0;
}
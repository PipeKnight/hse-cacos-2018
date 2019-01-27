#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>

#define push(x) stack[depth++] = (x)
#define pop() stack[--depth]

enum { OUT = 0, IN = 1 };
enum { DIGITS = 10, ALPHABET = 26, MAXDEPTH = 1001, OPIND = 62 };

char conv(char c) {
    if (isdigit(c)) {
        return c - '0';
    }
    if (isupper(c)) {
        return c - 'A' + DIGITS;
    }
    return c - 'a' + DIGITS + ALPHABET;
}

char reconv(char i) {
    if (i < DIGITS) {
        return i + '0';
    }
    if (i < DIGITS + ALPHABET) {
        return i - DIGITS + 'A';
    }
    return i - DIGITS - ALPHABET + 'a';
}

void print(uint64_t x) {
    bool fl = false;
    for (int j = 0; j < OPIND; ++j) {
        if ((x >> j) & 1) {
            fl = true;
            putchar(reconv(j));
        }
    }
    if (!fl) {
        putchar('#');
    }
    putchar('\n');
}

int main () {
    uint64_t stack[MAXDEPTH];
    unsigned depth = 0;
    char state = OUT;
    char c;
    uint64_t cur, a, b;
    while ((c = getchar()) != EOF) {
        if (state == OUT) {
            if (!isspace(c)) {
                if (isalnum(c)) {
                    state = IN;
                    cur = 1ull << conv(c);
                }
                else if (c == '#') {
                    push(0);
                }
                else {
                    a = pop();
                    if (c == '~') {
                        push(~a);
                        continue;
                    }
                    b = pop();
                    if (c == '&') {
                        push(a & b);
                    }
                    else if (c == '|') {
                        push(a | b);
                    }
                    else if (c == '^') {
                        push(a ^ b);
                    }
                }
            }
        }
        else if (state == IN) {
            if (isspace(c)) {
                push(cur);
                state = OUT;
                cur = 0;
            }
            else {
                cur |= 1ull << conv(c);
            }
        }
    }
    print(stack[0]);
    return 0;
}

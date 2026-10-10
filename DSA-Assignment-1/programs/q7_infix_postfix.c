#include <stdio.h>
#include <ctype.h>
#include <string.h>
char st[50]; int top = -1;
void push(char c) { st[++top] = c; }
char pop() { return st[top--]; }
int prec(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}
void convert(char *in, int show) {
    char out[50]; int k = 0, i;
    top = -1;
    if (show) printf("%-8s %-8s %s\n", "Symbol", "Stack", "Postfix");
    for (i = 0; in[i]; i++) {
        char c = in[i];
        if (isalnum(c)) out[k++] = c;
        else if (c == '(') push(c);
        else if (c == ')') { while (top != -1 && st[top] != '(') out[k++] = pop(); pop(); }
        else {
            while (top != -1 && prec(st[top]) >= prec(c)) out[k++] = pop();
            push(c);
        }
        if (show) { out[k] = 0; st[top + 1] = 0; printf("%-8c %-8s %s\n", c, st, out); }
    }
    while (top != -1) out[k++] = pop();
    out[k] = 0;
    printf("Postfix of %s = %s\n\n", in, out);
}
int main() {
    convert("A+B*C-D", 1);
    convert("(A+B)*(C-D)", 1);
    convert("A*(B+C)/D", 1);
    return 0;
}

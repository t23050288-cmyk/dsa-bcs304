#include <stdio.h>
#include <ctype.h>
int st[50], top = -1;
int evaluate(char *p) {
    int i, a, b;
    for (i = 0; p[i]; i++) {
        if (p[i] == ' ') continue;
        if (isdigit(p[i])) st[++top] = p[i] - '0';
        else {
            b = st[top--]; a = st[top--];
            switch (p[i]) {
                case '+': st[++top] = a + b; break;
                case '-': st[++top] = a - b; break;
                case '*': st[++top] = a * b; break;
                case '/': st[++top] = a / b; break;
            }
        }
    }
    return st[top--];
}
int main() {
    printf("Result = %d\n", evaluate("62/3-42*+"));
    return 0;
}

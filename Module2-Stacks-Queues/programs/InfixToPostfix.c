/* Infix to postfix conversion using a stack.
   Answers: "Convert the following infix expression to postfix expression using stack",
            "Translate the following infix expressions to postfix form using stack" */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char stack[50];
int top = -1;

void push(char c) { stack[++top] = c; }
char pop() { return stack[top--]; }

int precedence(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

int isRightAssoc(char c) { return c == '^'; }

void infixToPostfix(char *infix, char *postfix) {
    int i, k = 0;
    for (i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];
        if (isalnum(c)) {
            postfix[k++] = c;
        } else if (c == '(') {
            push(c);
        } else if (c == ')') {
            while (top != -1 && stack[top] != '(') postfix[k++] = pop();
            pop();  /* discard the '(' */
        } else {    /* operator */
            while (top != -1 && stack[top] != '(' &&
                   (precedence(stack[top]) > precedence(c) ||
                    (precedence(stack[top]) == precedence(c) && !isRightAssoc(c)))) {
                postfix[k++] = pop();
            }
            push(c);
        }
    }
    while (top != -1) postfix[k++] = pop();
    postfix[k] = '\0';
}

int main() {
    char *tests[] = {
        "A+(B*C-(D/E^F)*G)*H",
        "A*(B*C+D*E)+F",
        "((A*B)+C)/D",
        "A*B*C+D"
    };
    for (int t = 0; t < 4; t++) {
        top = -1;   /* reset stack between tests */
        char postfix[50];
        infixToPostfix(tests[t], postfix);
        printf("Infix  : %s\n", tests[t]);
        printf("Postfix: %s\n\n", postfix);
    }
    return 0;
}

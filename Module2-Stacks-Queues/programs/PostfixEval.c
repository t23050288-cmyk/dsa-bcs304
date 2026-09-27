/* Evaluate a postfix expression using a stack.
   Answers: "Write an algorithm to evaluate a postfix expression and apply the same",
            "Write a C function to evaluate postfix expression" */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int stack[50];
int top = -1;

void push(int x) { stack[++top] = x; }
int pop() { return stack[top--]; }

int evalPostfix(char *expr) {
    int i = 0;
    char token[10];
    top = -1;
    while (sscanf(expr + i, "%s", token) == 1) {
        if (isdigit(token[0])) {
            push(atoi(token));
        } else {
            int op2 = pop();
            int op1 = pop();
            switch (token[0]) {
                case '+': push(op1 + op2); break;
                case '-': push(op1 - op2); break;
                case '*': push(op1 * op2); break;
                case '/': push(op1 / op2); break;
            }
        }
        i += strlen(token);
        while (expr[i] == ' ') i++;
        if (expr[i] == '\0') break;
    }
    return pop();
}

int main() {
    printf("6 2 / 3 - 4 2 * + = %d\n", evalPostfix("6 2 / 3 - 4 2 * +"));
    printf("2 3 1 * + 9 -     = %d\n", evalPostfix("2 3 1 * + 9 -"));
    return 0;
}

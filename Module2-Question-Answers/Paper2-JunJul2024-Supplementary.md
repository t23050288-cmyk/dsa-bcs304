# BCS304 — June/July 2024 Supplementary Exam
## Module 2: Stacks, Stack Applications & Queues

---

## Q.2 b) Convert the following infix expression to postfix expression using stack: A+(B*C-(D/E^F)*G)*H. [10]

### Definition
Postfix (Reverse Polish) notation places the operator **after** its operands,
removing the need for parentheses/precedence rules during evaluation.

### Precedence Table

| Precedence | Operators | Associativity |
|---|---|---|
| Highest | `^` | Right to left |
| Middle | `* /` | Left to right |
| Lowest | `+ -` | Left to right |

### Manual Conversion (fully-parenthesize method)
```
Step 1 — Fully parenthesize:
(A+(((B*C)-((D/(E^F))*G))*H))

Step 2 — Move each operator to its closing paren, innermost first:
(E^F)              -> EF^
(D/(E^F))          -> DEF^/
(B*C)              -> BC*
((D/(E^F))*G)      -> DEF^/G*
((B*C)-(...))      -> BC*DEF^/G*-
(((...))*H)        -> BC*DEF^/G*-H*
(A+(...))          -> ABC*DEF^/G*-H*+
```

**Result: `A B C * D E F ^ / G * - H * +`**

### Easiest Program (`programs/InfixToPostfix.c`)
```c
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
        if (isalnum(c)) postfix[k++] = c;
        else if (c == '(') push(c);
        else if (c == ')') {
            while (top != -1 && stack[top] != '(') postfix[k++] = pop();
            pop();
        } else {
            while (top != -1 && stack[top] != '(' &&
                   (precedence(stack[top]) > precedence(c) ||
                    (precedence(stack[top]) == precedence(c) && !isRightAssoc(c))))
                postfix[k++] = pop();
            push(c);
        }
    }
    while (top != -1) postfix[k++] = pop();
    postfix[k] = '\0';
}

int main() {
    char infix[] = "A+(B*C-(D/E^F)*G)*H";
    char postfix[50];
    infixToPostfix(infix, postfix);
    printf("Infix  : %s\n", infix);
    printf("Postfix: %s\n", postfix);
    return 0;
}
```

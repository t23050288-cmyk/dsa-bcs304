# 4. Evaluation of Postfix Expression

Covers: "Write an algorithm to evaluate a postfix expression and apply the same for
the given postfix expression", "Write a C function to evaluate postfix expression",
"Write a function to evaluate the postfix expression. Illustrate the same...".

---

## 4.1 The Algorithm

**Definition:** Postfix expressions are evaluated using a single **left-to-right**
scan with a stack — operands are pushed, and whenever an operator is found, the
required number of operands are popped, the operation applied, and the result pushed
back.

**Points:**
1. Scan the postfix expression left to right, one token at a time.
2. If the token is an **operand**, push it onto the stack.
3. If the token is an **operator**, pop the top **two** operands (`op2` first, then
   `op1`), compute `op1 <operator> op2`, and push the result back.
4. Continue until the expression ends.
5. The final value left on the stack is the **result** of the expression.
6. No parentheses or precedence rules are needed — the postfix order already
   encodes the evaluation order.

### Syntax
```c
if (token is operand) push(token);
else {
    op2 = pop();
    op1 = pop();
    push(op1 <operator> op2);
}
```

---

## 4.2 Worked Example — `6 2 / 3 - 4 2 * +`

| Token | Action | Stack after |
|---|---|---|
| 6 | push | [6] |
| 2 | push | [6, 2] |
| / | pop 2,6 → 6/2=3, push | [3] |
| 3 | push | [3, 3] |
| - | pop 3,3 → 3-3=0, push | [0] |
| 4 | push | [0, 4] |
| 2 | push | [0, 4, 2] |
| * | pop 2,4 → 4*2=8, push | [0, 8] |
| + | pop 8,0 → 0+8=8, push | [8] |

**Result: 8**

---

## 4.3 Worked Example — `2 3 1 * + 9 -`

| Token | Action | Stack after |
|---|---|---|
| 2 | push | [2] |
| 3 | push | [2, 3] |
| 1 | push | [2, 3, 1] |
| * | pop 1,3 → 3*1=3, push | [2, 3] |
| + | pop 3,2 → 2+3=5, push | [5] |
| 9 | push | [5, 9] |
| - | pop 9,5 → 5-9=-4, push | [-4] |

**Result: -4**

---

## 4.4 Worked Example — `ABC-D*+E$F+` with A=6, B=3, C=2, D=5, E=1, F=7

(`$` denotes exponentiation, the classic textbook notation for `^`.)

| Token | Action | Stack after |
|---|---|---|
| A(6) | push | [6] |
| B(3) | push | [6, 3] |
| C(2) | push | [6, 3, 2] |
| - | pop 2,3 → 3-2=1, push | [6, 1] |
| D(5) | push | [6, 1, 5] |
| * | pop 5,1 → 1*5=5, push | [6, 5] |
| + | pop 5,6 → 6+5=11, push | [11] |
| E(1) | push | [11, 1] |
| $ | pop 1,11 → 11^1=11, push | [11] |
| F(7) | push | [11, 7] |
| + | pop 7,11 → 11+7=18, push | [18] |

**Result: 18**

### Easiest Program (`programs/PostfixEval.c` — generic, works for any digit-only postfix)
```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int stack[50];
int top = -1;

void push(int x) { stack[++top] = x; }
int pop() { return stack[top--]; }

int evalPostfix(char *expr) {
    int i = 0;
    char token[10];
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
```

**Smallest Program (hardcoded trace of `2 3 1 * + 9 -`):**
```c
#include <stdio.h>
int main() { int s[10],t=-1; s[++t]=2;s[++t]=3;s[++t]=1; int b=s[t--],a=s[t--]; s[++t]=a*b; s[++t]=9; int b2=s[t--],a2=s[t--]; s[++t]=a2-b2; printf("%d\n", s[t]); return 0; }
```

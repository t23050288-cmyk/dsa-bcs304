# 3. Stack Applications — Polish Notation & Infix-to-Postfix Conversion

Covers: "Convert the following infix expression to postfix expression using stack",
"Write the Postfix form of the following using stack", "Translate the following
infix expressions to postfix form using stack".

---

## 3.1 Polish Notation — the 3 Expression Forms

**Definition:** An expression can be written in three notations, depending on where
the operator is placed relative to its operands.

**Points:**
1. **Infix** — operator is placed **between** operands. Example: `A + B`.
   Needs parentheses/precedence rules to resolve ambiguity.
2. **Prefix (Polish notation)** — operator is placed **before** its operands.
   Example: `+ A B`.
3. **Postfix (Reverse Polish notation)** — operator is placed **after** its
   operands. Example: `A B +`.
4. Postfix is preferred for computer evaluation because it needs **no
   parentheses** and **no precedence rules** — a simple left-to-right scan with a
   stack evaluates it directly (see file 04).

---

## 3.2 Operator Precedence & Associativity (needed for conversion)

| Precedence | Operators | Associativity |
|---|---|---|
| Highest | `^` (exponent) | Right to left |
| Middle | `* /` | Left to right |
| Lowest | `+ -` | Left to right |

**Points:**
1. Higher precedence operators are evaluated (and placed in postfix) before lower
   precedence ones.
2. Parentheses `()` override precedence — always resolve inside-out.
3. `^` is **right-associative** — for `E^F` chains like `A^B^C`, it groups as `A^(B^C)`.

---

## 3.3 Infix to Postfix — the Conversion Algorithm

**Definition:** Converts an infix expression to postfix using a stack to temporarily
hold operators until their correct output position is determined.

**Points (algorithm):**
1. Scan the infix expression left to right, one token at a time.
2. If the token is an **operand**, append it directly to the output.
3. If the token is `(`, push it onto the stack.
4. If the token is `)`, pop and output operators until a matching `(` is found;
   discard both parentheses.
5. If the token is an **operator**, pop and output all operators from the stack that
   have **greater or equal precedence** (for left-associative ops), then push the
   current operator. (For right-associative `^`, only pop if stack-top precedence is
   strictly **greater**.)
6. At the end, pop all remaining operators from the stack to the output.

**Manual method (equivalent, easier to do by hand in an exam):**
1. Fully parenthesize the expression according to precedence.
2. Move each operator to replace its matching **right** parenthesis.
3. Delete all parentheses.

### Worked Example 1 — `A+(B*C-(D/E^F)*G)*H`
```
Step 1 — Fully parenthesize:
(A+(((B*C)-((D/(E^F))*G))*H))

Step 2 — Move each operator to its closing paren, innermost first:
(E^F)              -> EF^
(D/(E^F))          -> D EF^ /      = DEF^/
(B*C)              -> BC*
((D/(E^F))*G)      -> DEF^/ G *    = DEF^/G*
((B*C)-(...))      -> BC* DEF^/G* -  = BC*DEF^/G*-
(((...))*H)        -> BC*DEF^/G*- H * = BC*DEF^/G*-H*
(A+(...))          -> A BC*DEF^/G*-H* + = ABC*DEF^/G*-H*+

Result: A B C * D E F ^ / G * - H * +
```

### Worked Example 2 — `A*(B*C+D*E)+F`
```
(B*C) -> BC*
(D*E) -> DE*
(B*C+D*E) -> BC*DE*+
A*(...) -> A BC*DE*+ * = ABC*DE*+*
(...)+F -> ABC*DE*+* F + = ABC*DE*+*F+

Result: A B C * D E * + * F +
```

### Worked Example 3 — `(a+(b*c)/(d-e))`
```
(b*c) -> bc*
(d-e) -> de-
(b*c)/(d-e) -> bc* de- / = bc*de-/
a+(...) -> a bc*de-/ + = abc*de-/+

Result: a b c * d e - / +
```

### Worked Example 4 — `((A*B)+C)/D`
```
(A*B) -> AB*
(A*B)+C -> AB* C + = AB*C+
((A*B)+C)/D -> AB*C+ D / = AB*C+D/

Result: A B * C + D /
```

### Worked Example 5 — `A*B*C+D`
```
A*B -> AB*
(A*B)*C -> AB* C * = AB*C*
(A*B*C)+D -> AB*C* D + = AB*C*D+

Result: A B * C * D +
```

### Worked Example 6 — `(A+(B*C)/(D-E))`
```
(B*C) -> BC*
(D-E) -> DE-
(B*C)/(D-E) -> BC* DE- / = BC*DE-/
A+(...) -> A BC*DE-/ + = ABC*DE-/+

Result: A B C * D E - / +
```

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
    char infix[] = "A+(B*C-(D/E^F)*G)*H";
    char postfix[50];
    infixToPostfix(infix, postfix);
    printf("Infix  : %s\n", infix);
    printf("Postfix: %s\n", postfix);
    return 0;
}
```

**Smallest Program (simple case, no parentheses/exponent):**
```c
#include <stdio.h>
int main() { printf("A*B+C -> AB*C+\n"); return 0; }
```

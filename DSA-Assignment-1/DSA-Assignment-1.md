# DSA Assignment 1

Subject: Data Structures and Applications (BCS304) | Semester III | VTU

Covers Module 1 to Module 2.5. All the C programs are in the `programs/` folder. Every program was compiled and run, and the outputs shown here are the real outputs.

---

## 1. Define data structure. Explain the classification of data structures into Primitive and Non-Primitive with a neat diagram. Further classify non-primitive data structures into Linear and Non-Linear with suitable examples.

**Definition:** A data structure is a way of storing and organizing data in the computer memory so that it can be used efficiently. It also tells us which operations (insert, delete, search, sort) can be done on that data.

**Why we need it:**

1. It stores a large amount of data in an organized way.
2. It makes searching, inserting and deleting faster.
3. It saves memory and processing time.
4. Real life examples: contact list in a phone (array), undo option in an editor (stack), printer queue (queue).

### Classification

```
                      DATA STRUCTURES
                            |
            +---------------+----------------+
            |                                |
        PRIMITIVE                       NON-PRIMITIVE
     (int, float, char,                      |
      double, pointer)            +----------+-----------+
                                  |                      |
                               LINEAR               NON-LINEAR
                                  |                      |
                      +-----------+--------+        +----+-----+
                      |                    |        |          |
                  Static              Dynamic     Trees      Graphs
                  (Array)         (Stack, Queue,
                                   Linked List)
```

### A. Primitive data structures

1. These are the basic data types already provided by the C language.
2. They store only a single value.
3. The machine can directly work on them.
4. Examples: `int`, `float`, `char`, `double`, pointer.

```c
int a = 10;
char c = 'A';
float f = 3.5;
```

### B. Non-primitive data structures

1. These are made by combining primitive data types.
2. They store a group of values, and the values may be of the same or different types.
3. They are divided into two types: linear and non-linear.

#### (i) Linear data structures

1. The elements are arranged one after another in a sequence.
2. Each element has one previous element and one next element (except the first and last).
3. We can go through all elements in a single run.
4. Examples:
   - **Array** : fixed size, same type elements. `int a[5];`
   - **Stack** : LIFO, insertion and deletion at one end (top).
   - **Queue** : FIFO, insertion at rear and deletion at front.
   - **Linked list** : nodes connected using pointers.

```
Array :  [10][20][30][40]
Stack :  | 30 | <- top        Queue :  front -> 10 20 30 <- rear
         | 20 |
         | 10 |
```

#### (ii) Non-linear data structures

1. The elements are not in a sequence. One element can be connected to many elements.
2. They show a hierarchy or a network.
3. We cannot go through all elements in a single run.
4. Examples:
   - **Tree** : hierarchical, like a family tree or folders in a computer.
   - **Graph** : a set of nodes connected by edges, like a road map or social network.

```
Tree :       A              Graph :   A --- B
            / \                       |  \  |
           B   C                      C --- D
```

### Difference

| Linear | Non-linear |
|---|---|
| Elements in a sequence | Elements in a hierarchy or network |
| One-level data | Multi-level data |
| Easy to implement | Hard to implement |
| Array, stack, queue, linked list | Tree, graph |

---

## 2. Explain pointers in C with declaration, initialization, dereferencing and pointer arithmetic. Explain malloc(), calloc(), realloc() and free() with syntax and suitable examples.

**Definition:** A pointer is a variable that stores the address of another variable.

### A. Declaration

**Syntax:**
```c
dataType *pointerName;
```
```c
int *p;          /* p can store the address of an int variable */
```
The `*` shows that the variable is a pointer.

### B. Initialization

A pointer is initialized with the address of a variable, using the address operator `&`.

```c
int a = 10;
int *p = &a;     /* p now stores the address of a */
```

### C. Dereferencing

Getting the value stored at the address in the pointer, using the `*` operator.

```c
printf("%d", *p);    /* prints 10 */
*p = 20;             /* a becomes 20 */
```

### D. Pointer arithmetic

1. A pointer can be incremented, decremented, added or subtracted with an integer.
2. `p + 1` does not add 1 byte. It moves to the next element of the same data type. For an `int` pointer it moves 4 bytes.
3. Two pointers of the same array can be subtracted to find the number of elements between them.
4. Pointers cannot be added, multiplied or divided with each other.

```c
int arr[3] = {10, 20, 30};
int *q = arr;
printf("%d %d %d", *q, *(q + 1), *(q + 2));   /* 10 20 30 */
q++;                                          /* now q points to 20 */
```

### E. Dynamic memory allocation

Memory is allocated at run time from the heap. The header file is `<stdlib.h>`.

#### 1. malloc()

Allocates a block of memory of the given size in bytes. The memory is not initialized (it has garbage values). Returns `NULL` if it fails.

**Syntax:**
```c
ptr = (castType *) malloc(size_in_bytes);
```
```c
int *m = (int *) malloc(3 * sizeof(int));
```

#### 2. calloc()

Allocates memory for an array of elements, and sets every byte to zero.

**Syntax:**
```c
ptr = (castType *) calloc(numberOfElements, sizeOfEachElement);
```
```c
int *c = (int *) calloc(3, sizeof(int));     /* c[0], c[1], c[2] are all 0 */
```

#### 3. realloc()

Changes (increases or decreases) the size of memory that was already allocated. The old values are kept.

**Syntax:**
```c
ptr = (castType *) realloc(ptr, newSize_in_bytes);
```
```c
m = (int *) realloc(m, 5 * sizeof(int));
```

#### 4. free()

Releases the memory that was allocated dynamically, so it can be used again. If we forget this, we get a memory leak.

**Syntax:**
```c
free(ptr);
```
```c
free(m);
free(c);
```

### Program

```c
#include <stdio.h>
#include <stdlib.h>
int main() {
    int a = 10;
    int *p = &a;
    printf("a = %d, *p = %d\n", a, *p);
    *p = 20;
    printf("a after *p = 20 : %d\n", a);

    int arr[3] = {10, 20, 30};
    int *q = arr;
    printf("%d %d %d\n", *q, *(q + 1), *(q + 2));
    q++;
    printf("after q++ : %d\n", *q);

    int *m = (int *)malloc(3 * sizeof(int));
    int *c = (int *)calloc(3, sizeof(int));
    m[0] = 5; m[1] = 6; m[2] = 7;
    printf("malloc: %d %d %d | calloc: %d %d %d\n", m[0], m[1], m[2], c[0], c[1], c[2]);
    m = (int *)realloc(m, 5 * sizeof(int));
    m[3] = 8; m[4] = 9;
    printf("realloc: %d %d %d %d %d\n", m[0], m[1], m[2], m[3], m[4]);
    free(m);
    free(c);
    return 0;
}
```

**Output:**
```
a = 10, *p = 10
a after *p = 20 : 20
10 20 30
after q++ : 20
malloc: 5 6 7 | calloc: 0 0 0
realloc: 5 6 7 8 9
```

### malloc() vs calloc()

| malloc() | calloc() |
|---|---|
| One argument (total bytes) | Two arguments (count, size) |
| Memory has garbage values | Memory is set to zero |
| A little faster | A little slower |

---

## 3. Define structure and union. Explain their declaration and memory allocation with examples. Compare structures and unions with respect to memory utilization, storage and applications.

### Structure

**Definition:** A structure is a user-defined data type that groups variables of different data types under one name. Every member gets its own separate memory.

**Syntax:**
```c
struct structureName { dataType member1; dataType member2; };
```
```c
struct Student {
    int id;          /* 4 bytes */
    float marks;     /* 4 bytes */
    char grade;      /* 1 byte  */
};
```

**Memory allocation:**

1. The memory is the sum of all members (with padding).
2. Here `4 + 4 + 1 = 9`, but the compiler adds padding to make it a multiple of 4, so the size is **12 bytes**.
3. All members can be used at the same time.

```
struct Student :  | id (4) | marks (4) | grade (1)+pad(3) |   = 12 bytes
```

### Union

**Definition:** A union is also a user-defined data type that groups variables of different types, but all members share the same memory location.

**Syntax:**
```c
union unionName { dataType member1; dataType member2; };
```
```c
union Data {
    int i;           /* 4 bytes */
    float f;         /* 4 bytes */
    char c;          /* 1 byte  */
};
```

**Memory allocation:**

1. The memory is equal to the size of the largest member. Here it is **4 bytes**.
2. Only one member can hold a value at a time. If we store a new value, the old value is lost.

```
union Data :  | i / f / c all share the same 4 bytes |
```

### Program

```c
#include <stdio.h>
struct Student { int id; float marks; char grade; };
union Data { int i; float f; char c; };
int main() {
    struct Student s = {1, 85.5, 'A'};
    union Data d;
    printf("size of struct = %zu\n", sizeof(struct Student));
    printf("size of union  = %zu\n", sizeof(union Data));
    d.i = 10;
    printf("d.i = %d\n", d.i);
    d.f = 3.5;
    printf("d.f = %.1f\n", d.f);
    printf("%d %.1f %c\n", s.id, s.marks, s.grade);
    return 0;
}
```

**Output:**
```
size of struct = 12
size of union  = 4
d.i = 10
d.f = 3.5
1 85.5 A
```

### Comparison

| Point | Structure | Union |
|---|---|---|
| Keyword | `struct` | `union` |
| Memory utilization | Sum of all members (more memory) | Size of the largest member (less memory) |
| Storage | Each member has its own separate memory | All members share one memory location |
| Access | All members can be used at the same time | Only one member can be used at a time |
| Changing a member | Does not affect the others | Overwrites the other members |
| Size in the example | 12 bytes | 4 bytes |
| Applications | Records like student, employee, linked list node | Saving memory, device registers, one value of many possible types |

---

## 4. Convert the following matrix into triplet representation and explain each field.

```
0 0 3 0 0
0 4 0 0 0
5 0 0 0 8
0 0 0 6 0
```

**Definition:** A sparse matrix is a matrix in which most of the elements are zero. To save memory we store only the non-zero elements, using a table of three columns called the triplet representation.

### Fields of the triplet

1. **Row** : the row number of the non-zero element.
2. **Column** : the column number of the non-zero element.
3. **Value** : the non-zero value itself.
4. The first row (row 0) of the table is a header. It stores: total rows, total columns, total number of non-zero elements.
5. Indexes start from 0.

### Steps

1. The matrix has 4 rows and 5 columns.
2. Scan row by row and note each non-zero element.
   - Row 0: value 3 at column 2.
   - Row 1: value 4 at column 1.
   - Row 2: value 5 at column 0, and value 8 at column 4.
   - Row 3: value 6 at column 3.
3. Count of non-zero elements = 5.

### Triplet representation

| Index | Row | Column | Value |
|---|---|---|---|
| 0 (header) | 4 | 5 | 5 |
| 1 | 0 | 2 | 3 |
| 2 | 1 | 1 | 4 |
| 3 | 2 | 0 | 5 |
| 4 | 2 | 4 | 8 |
| 5 | 3 | 3 | 6 |

The header says: 4 rows, 5 columns, 5 non-zero elements.

### Saving of memory

1. Normal storage: 4 x 5 = 20 elements.
2. Triplet storage: 6 x 3 = 18 elements. The saving is bigger when the matrix is larger and has fewer non-zero elements.

### Program

```c
#include <stdio.h>
int main() {
    int a[4][5] = {{0,0,3,0,0},{0,4,0,0,0},{5,0,0,0,8},{0,0,0,6,0}};
    int t[20][3], k = 1, i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 5; j++)
            if (a[i][j] != 0) { t[k][0] = i; t[k][1] = j; t[k][2] = a[i][j]; k++; }
    t[0][0] = 4; t[0][1] = 5; t[0][2] = k - 1;
    printf("Row Col Value\n");
    for (i = 0; i < k; i++) printf("%3d %3d %5d\n", t[i][0], t[i][1], t[i][2]);
    return 0;
}
```

**Output:**
```
Row Col Value
  4   5     5
  0   2     3
  1   1     4
  2   0     5
  2   4     8
  3   3     6
```

---

## 5. For the given matrix, construct its triplet representation and find its transpose.

```
 15   0   0  22   0  -15
  0  11   3   0   0    0
  0   0   0  -6   0    0
  0   0   0   0   0    0
 91   0   0   0   0    0
  0   0  28   0   0    0
```

### Step 1: Triplet representation

The matrix is 6 x 6. Scan row by row.

- Row 0: 15 at (0,0), 22 at (0,3), -15 at (0,5)
- Row 1: 11 at (1,1), 3 at (1,2)
- Row 2: -6 at (2,3)
- Row 3: no non-zero element
- Row 4: 91 at (4,0)
- Row 5: 28 at (5,2)

Total non-zero elements = 8.

| Index | Row | Column | Value |
|---|---|---|---|
| 0 (header) | 6 | 6 | 8 |
| 1 | 0 | 0 | 15 |
| 2 | 0 | 3 | 22 |
| 3 | 0 | 5 | -15 |
| 4 | 1 | 1 | 11 |
| 5 | 1 | 2 | 3 |
| 6 | 2 | 3 | -6 |
| 7 | 4 | 0 | 91 |
| 8 | 5 | 2 | 28 |

### Step 2: Transpose

**Idea:** The transpose of a matrix is got by changing rows into columns. So for every triplet `(row, col, value)` we write `(col, row, value)`. After swapping, the triplets are arranged again in increasing order of the new row number.

**Method (column by column):**

1. In the header, swap rows and columns (6 and 6 remain the same here). The count stays 8.
2. Take column 0 of the original, and write all its triplets after swapping.
3. Then take column 1, then column 2, and so on up to column 5.

| Original column | Triplets found (row, col, value) | After swapping |
|---|---|---|
| 0 | (0,0,15), (4,0,91) | (0,0,15), (0,4,91) |
| 1 | (1,1,11) | (1,1,11) |
| 2 | (1,2,3), (5,2,28) | (2,1,3), (2,5,28) |
| 3 | (0,3,22), (2,3,-6) | (3,0,22), (3,2,-6) |
| 4 | none | none |
| 5 | (0,5,-15) | (5,0,-15) |

### Transpose in triplet form

| Index | Row | Column | Value |
|---|---|---|---|
| 0 (header) | 6 | 6 | 8 |
| 1 | 0 | 0 | 15 |
| 2 | 0 | 4 | 91 |
| 3 | 1 | 1 | 11 |
| 4 | 2 | 1 | 3 |
| 5 | 2 | 5 | 28 |
| 6 | 3 | 0 | 22 |
| 7 | 3 | 2 | -6 |
| 8 | 5 | 0 | -15 |

### Transpose matrix

```
 15   0   0   0  91   0
  0  11   0   0   0   0
  0   3   0   0   0  28
 22   0  -6   0   0   0
  0   0   0   0   0   0
-15   0   0   0   0   0
```

### Program

```c
#include <stdio.h>
int main() {
    int a[6][6] = {
        {15,0,0,22,0,-15},
        {0,11,3,0,0,0},
        {0,0,0,-6,0,0},
        {0,0,0,0,0,0},
        {91,0,0,0,0,0},
        {0,0,28,0,0,0}};
    int t[40][3], s[40][3], k = 1, i, j, c, n;
    for (i = 0; i < 6; i++)
        for (j = 0; j < 6; j++)
            if (a[i][j] != 0) { t[k][0] = i; t[k][1] = j; t[k][2] = a[i][j]; k++; }
    t[0][0] = 6; t[0][1] = 6; t[0][2] = k - 1;
    n = t[0][2];
    s[0][0] = t[0][1]; s[0][1] = t[0][0]; s[0][2] = n;
    k = 1;
    for (c = 0; c < t[0][1]; c++)
        for (i = 1; i <= n; i++)
            if (t[i][1] == c) { s[k][0] = t[i][1]; s[k][1] = t[i][0]; s[k][2] = t[i][2]; k++; }
    for (i = 0; i <= n; i++) printf("%3d %3d %5d\n", s[i][0], s[i][1], s[i][2]);
    return 0;
}
```

The program output for the transpose is the same as the table above (the full program with both tables is in `programs/q5_transpose.c`).

---

## 6. Explain PUSH, POP, PEEK, IsEmpty and IsFull operations. Discuss stack overflow and underflow conditions.

**Definition:** A stack is a linear data structure in which insertion and deletion are done at only one end, called the top. It follows the LIFO principle (Last In, First Out). Real life example: a pile of plates.

**Syntax (array stack):**
```c
#define MAX 5
int stack[MAX], top = -1;
```

1. `top = -1` means the stack is empty.
2. `top` always holds the index of the last inserted element.

### Operations

#### 1. PUSH (insert)

1. First check if the stack is full. If full, show overflow.
2. Otherwise increase `top` by 1 and store the element at `stack[top]`.

```c
void push(int x) {
    if (top == MAX - 1) { printf("Stack Overflow\n"); return; }
    stack[++top] = x;
}
```

#### 2. POP (delete)

1. First check if the stack is empty. If empty, show underflow.
2. Otherwise take `stack[top]` and decrease `top` by 1.

```c
int pop() {
    if (top == -1) { printf("Stack Underflow\n"); return -1; }
    return stack[top--];
}
```

#### 3. PEEK

Shows the top element without removing it. `top` does not change.

```c
int peek() {
    if (top == -1) { printf("Stack is empty\n"); return -1; }
    return stack[top];
}
```

#### 4. IsEmpty

Returns true when there is no element.

```c
int isEmpty() { return top == -1; }
```

#### 5. IsFull

Returns true when there is no space for a new element.

```c
int isFull() { return top == MAX - 1; }
```

### Stack overflow and underflow

| | Overflow | Underflow |
|---|---|---|
| Meaning | Trying to push into a full stack | Trying to pop from an empty stack |
| Condition | `top == MAX - 1` | `top == -1` |
| Happens during | PUSH | POP |

Example with MAX = 5: after pushing 10, 20, 30, 40, 50, the top is 4. A push of 60 gives overflow. After removing all five elements the top is -1, and one more pop gives underflow.

```
push(10)  push(20)  push(30)      pop()
 | |      | |       |30|<-top    |20|<-top
 | |      |20|<-top |20|         |10|
 |10|<-top|10|      |10|
```

### Program

```c
#include <stdio.h>
#define MAX 5
int stack[MAX], top = -1;
int isEmpty() { return top == -1; }
int isFull()  { return top == MAX - 1; }
void push(int x) {
    if (isFull()) { printf("Stack Overflow\n"); return; }
    stack[++top] = x;
    printf("%d pushed\n", x);
}
int pop() {
    if (isEmpty()) { printf("Stack Underflow\n"); return -1; }
    return stack[top--];
}
int peek() {
    if (isEmpty()) { printf("Stack is empty\n"); return -1; }
    return stack[top];
}
int main() {
    push(10); push(20); push(30); push(40); push(50);
    push(60);
    printf("peek = %d\n", peek());
    printf("popped %d\n", pop());
    while (!isEmpty()) pop();
    pop();
    return 0;
}
```

**Output:**
```
10 pushed
20 pushed
30 pushed
40 pushed
50 pushed
Stack Overflow
peek = 50
popped 50
Stack Underflow
```

---

## 7. Explain the algorithm for converting an infix expression into postfix using a stack. Convert the following expressions: a) A+B*C-D  b) (A+B)*(C-D)  c) A*(B+C)/D. Show the stack contents at each step.

**Definition:**
- Infix: the operator is between the operands, like `A+B`.
- Postfix: the operator is after the operands, like `AB+`. It does not need brackets, and the computer can evaluate it easily.

**Precedence of operators:**

| Operator | Precedence |
|---|---|
| `^` | 3 (highest) |
| `*`, `/` | 2 |
| `+`, `-` | 1 |
| `(` | lowest, inside the stack |

### Algorithm

1. Read the infix expression from left to right, one symbol at a time.
2. If the symbol is an **operand** (A, B, 1, 2), add it directly to the postfix output.
3. If the symbol is `(`, push it on the stack.
4. If the symbol is `)`, pop from the stack and add to the output until `(` comes. Then remove the `(` and do not output it.
5. If the symbol is an **operator**:
   - While the stack is not empty and the top operator has precedence equal to or higher than this operator, pop it and add it to the output.
   - Then push the current operator on the stack.
6. After reading the whole expression, pop all remaining operators from the stack and add them to the output.

### a) A+B*C-D

| Symbol | Stack | Postfix |
|---|---|---|
| A | | A |
| + | + | A |
| B | + | AB |
| * | +* | AB |
| C | +* | ABC |
| - | - | ABC*+ |
| D | - | ABC*+D |
| end | | ABC*+D- |

Working: `*` has higher precedence than `+`, so it is pushed above `+`. When `-` comes, both `*` and `+` have precedence higher than or equal to it, so both are popped.

**Postfix = ABC\*+D-**

### b) (A+B)*(C-D)

| Symbol | Stack | Postfix |
|---|---|---|
| ( | ( | |
| A | ( | A |
| + | (+ | A |
| B | (+ | AB |
| ) | | AB+ |
| * | * | AB+ |
| ( | *( | AB+ |
| C | *( | AB+C |
| - | *(- | AB+C |
| D | *(- | AB+CD |
| ) | * | AB+CD- |
| end | | AB+CD-* |

**Postfix = AB+CD-\***

### c) A*(B+C)/D

| Symbol | Stack | Postfix |
|---|---|---|
| A | | A |
| * | * | A |
| ( | *( | A |
| B | *( | AB |
| + | *(+ | AB |
| C | *(+ | ABC |
| ) | * | ABC+ |
| / | / | ABC+* |
| D | / | ABC+*D |
| end | | ABC+*D/ |

Working: when `/` comes, the top `*` has equal precedence, so `*` is popped first (left to right), then `/` is pushed.

**Postfix = ABC+\*D/**

### Program

```c
#include <stdio.h>
#include <ctype.h>
char st[50]; int top = -1;
void push(char c) { st[++top] = c; }
char pop() { return st[top--]; }
int prec(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}
int main() {
    char in[] = "A+B*C-D", out[50]; int k = 0, i;
    for (i = 0; in[i]; i++) {
        char c = in[i];
        if (isalnum(c)) out[k++] = c;
        else if (c == '(') push(c);
        else if (c == ')') { while (st[top] != '(') out[k++] = pop(); pop(); }
        else {
            while (top != -1 && prec(st[top]) >= prec(c)) out[k++] = pop();
            push(c);
        }
    }
    while (top != -1) out[k++] = pop();
    out[k] = 0;
    printf("Postfix = %s\n", out);
    return 0;
}
```

**Output:** `Postfix = ABC*+D-` (the full program with all three expressions is in `programs/q7_infix_postfix.c`).

---

## 8. Explain postfix expression evaluation using a stack. Evaluate the following expression and show the stack contents after each operation: 6 2 / 3 - 4 2 * +. Also write a suitable C function for postfix evaluation.

**Definition:** Postfix evaluation means finding the value of a postfix expression using a stack. Operands are pushed on the stack, and when an operator comes, it works on the top two operands.

### Algorithm

1. Read the postfix expression from left to right.
2. If the symbol is an **operand**, push it on the stack.
3. If the symbol is an **operator**:
   - Pop the top element and call it `b` (second operand).
   - Pop the next element and call it `a` (first operand).
   - Calculate `a operator b`.
   - Push the result back on the stack.
4. After the whole expression is read, the one value left in the stack is the answer.

**Note:** The first popped value is the right operand. This matters for `-` and `/`. For example `6 2 /` gives `6 / 2`, not `2 / 6`.

### Evaluation of 6 2 / 3 - 4 2 * +

| Symbol | Action | Stack (bottom to top) |
|---|---|---|
| 6 | push 6 | 6 |
| 2 | push 2 | 6, 2 |
| / | b = 2, a = 6, 6 / 2 = 3, push 3 | 3 |
| 3 | push 3 | 3, 3 |
| - | b = 3, a = 3, 3 - 3 = 0, push 0 | 0 |
| 4 | push 4 | 0, 4 |
| 2 | push 2 | 0, 4, 2 |
| * | b = 2, a = 4, 4 * 2 = 8, push 8 | 0, 8 |
| + | b = 8, a = 0, 0 + 8 = 8, push 8 | 8 |

**Result = 8**

### C function

```c
#include <stdio.h>
#include <ctype.h>
int st[50], top = -1;

int evaluate(char *p) {
    int i, a, b;
    for (i = 0; p[i]; i++) {
        if (p[i] == ' ') continue;
        if (isdigit(p[i]))
            st[++top] = p[i] - '0';          /* operand: push */
        else {
            b = st[top--];                   /* second operand */
            a = st[top--];                   /* first operand  */
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
```

**Output:**
```
Result = 8
```

`p[i] - '0'` changes the character digit to its number value. This program works for single-digit operands.

---

## 9. Explain array representation of a queue. Write algorithms and a C program for enqueue(), dequeue() and display().

**Definition:** A queue is a linear data structure in which insertion is done at one end called the rear, and deletion is done at the other end called the front. It follows the FIFO principle (First In, First Out). Real life example: people standing in a ticket line.

### Array representation

1. A queue is stored in a one dimensional array of size MAX, with two variables `front` and `rear`.
2. `front` is the index of the first element, which is deleted next.
3. `rear` is the index of the last element, after which a new element is inserted.
4. At the start, `front = -1` and `rear = -1`, which means the queue is empty.
5. Queue is full when `rear == MAX - 1`.

**Syntax:**
```c
#define MAX 5
int queue[MAX], front = -1, rear = -1;
```

```
Index :   0    1    2    3    4
        [10] [20] [30] [  ] [  ]
         ^front    ^rear
```

### Algorithm for ENQUEUE (insert)

```
1. If rear == MAX - 1, print "Queue Overflow" and stop.
2. If front == -1, set front = 0.
3. Increase rear by 1.
4. Store the item at queue[rear].
5. Stop.
```

### Algorithm for DEQUEUE (delete)

```
1. If front == -1 or front > rear, print "Queue Underflow" and stop.
2. Take item = queue[front].
3. Increase front by 1.
4. If front > rear, set front = -1 and rear = -1.
5. Return item. Stop.
```

### Algorithm for DISPLAY

```
1. If front == -1, print "Queue is empty" and stop.
2. For i from front to rear, print queue[i].
3. Stop.
```

### Program

```c
#include <stdio.h>
#define MAX 5
int queue[MAX], front = -1, rear = -1;

void enqueue(int x) {
    if (rear == MAX - 1) { printf("Queue Overflow\n"); return; }
    if (front == -1) front = 0;
    queue[++rear] = x;
    printf("%d inserted\n", x);
}
void dequeue() {
    if (front == -1 || front > rear) { printf("Queue Underflow\n"); return; }
    printf("%d deleted\n", queue[front++]);
    if (front > rear) front = rear = -1;
}
void display() {
    int i;
    if (front == -1) { printf("Queue is empty\n"); return; }
    printf("Queue: ");
    for (i = front; i <= rear; i++) printf("%d ", queue[i]);
    printf("\n");
}
int main() {
    enqueue(10); enqueue(20); enqueue(30);
    display();
    dequeue();
    display();
    dequeue(); dequeue(); dequeue();
    return 0;
}
```

**Output:**
```
10 inserted
20 inserted
30 inserted
Queue: 10 20 30
10 deleted
Queue: 20 30
20 deleted
30 deleted
Queue Underflow
```

### Disadvantage

After some deletions, the empty places at the front can never be used again, because `rear` only moves forward. The queue may show "Overflow" even when there are free places. This is called false overflow, and it is solved by using a circular queue.

---

## 10. Explain the concept of multiple stacks. Describe how two stacks can be implemented in a single array with a neat diagram.

**Definition:** Multiple stacks means keeping two or more stacks inside one single array, so that the memory is shared and used properly.

### Why we need it

1. If we use two separate arrays, one stack may become full while the other array has a lot of empty space. This wastes memory.
2. In one shared array, either stack can use the free space, so overflow comes only when the whole array is full.

### Method for two stacks

1. Take one array of size SIZE.
2. **Stack 1** starts from the left end (index 0) and grows to the right. `top1` starts at `-1`.
3. **Stack 2** starts from the right end (index SIZE - 1) and grows to the left. `top2` starts at `SIZE`.
4. The two stacks grow towards each other.

### Diagram

```
Index :   0    1    2    3    4    5    6    7    8    9
        [10] [20] [30] [  ] [  ] [  ] [  ] [  ] [80] [90]
                   ^                             ^
                 top1 = 2                     top2 = 8

        Stack 1 grows ---->              <---- Stack 2 grows
```

### Conditions

| Condition | Check |
|---|---|
| Stack 1 empty | `top1 == -1` |
| Stack 2 empty | `top2 == SIZE` |
| Overflow (both stacks) | `top1 + 1 == top2` |

### Operations

```c
void push1(int x) {                       /* push in stack 1 */
    if (top1 + 1 == top2) { printf("Overflow\n"); return; }
    a[++top1] = x;
}
void push2(int x) {                       /* push in stack 2 */
    if (top2 - 1 == top1) { printf("Overflow\n"); return; }
    a[--top2] = x;
}
int pop1() { if (top1 == -1) { printf("Underflow 1\n"); return -1; } return a[top1--]; }
int pop2() { if (top2 == SIZE) { printf("Underflow 2\n"); return -1; } return a[top2++]; }
```

### Program

```c
#include <stdio.h>
#define SIZE 10
int a[SIZE], top1 = -1, top2 = SIZE;
void push1(int x) {
    if (top1 + 1 == top2) { printf("Overflow\n"); return; }
    a[++top1] = x;
}
void push2(int x) {
    if (top2 - 1 == top1) { printf("Overflow\n"); return; }
    a[--top2] = x;
}
int pop1() { if (top1 == -1) { printf("Underflow 1\n"); return -1; } return a[top1--]; }
int pop2() { if (top2 == SIZE) { printf("Underflow 2\n"); return -1; } return a[top2++]; }
int main() {
    push1(10); push1(20); push1(30);
    push2(90); push2(80);
    printf("pop1 = %d, pop2 = %d\n", pop1(), pop2());
    return 0;
}
```

**Output:**
```
pop1 = 30, pop2 = 80
```

Stack 1 gave 30 (its last inserted) and stack 2 gave 80 (its last inserted), which shows that both work as LIFO.

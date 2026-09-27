# 1. Stack — Definition, ADT & Operations

Covers: "Explain ADT stack", "Define Stack", "Define stack. With suitable example
write the array representation of stack".

---

## 1.1 What is a Stack?

**Definition:** A stack is an ordered list in which insertions and deletions are made
at only **one end**, called the **top**. Since the last element inserted is the first
one removed, a stack is also called a **Last-In-First-Out (LIFO)** list.

**Points:**
1. **push** = inserting an element onto the stack.
2. **pop** = removing (and returning) the top element from the stack.
3. Trying to `pop` an **empty** stack is called **underflow**.
4. Trying to `push` onto a **full** stack is called **overflow**.
5. Real-world example: a stack of plates — you add/remove from the top only.
6. A **system stack** is used internally by every program to manage function calls —
   each call creates a "stack frame" (activation record) holding local variables and
   the return address, pushed on entry and popped on return.

**Diagram (insert A, B, C, D, E then delete):**
```
push A -> [A]
push B -> [A, B]
push C -> [A, B, C]
push D -> [A, B, C, D]
push E -> [A, B, C, D, E]   <- top
pop    -> removes E first (LIFO)
```

---

## 1.2 Stack as an Abstract Data Type (ADT)

**Definition:** An ADT defines *what* operations a stack supports, without
specifying *how* they're implemented (array or linked list).

**Points (main + auxiliary operations):**
1. **Main operations:**
   - `push(data)` — inserts data onto the stack.
   - `pop()` — removes and returns the top element.
2. **Auxiliary operations:**
   - `top()` — returns the top element **without** removing it.
   - `size()` — returns the number of elements currently in the stack.
   - `isEmptyStack()` — checks whether the stack has any elements.
   - `isFullStack()` — checks whether the stack is full (only relevant for fixed-size
     array implementations).
3. `CreateS(max_stack_size)` — creates an empty stack of a given maximum size.

### Syntax (ADT structure)
```c
Stack CreateS(max_stack_size);
Boolean IsFull(stack);
Stack Add(stack, item);      /* push */
Boolean IsEmpty(stack);
Element Delete(stack);       /* pop */
```

**Smallest Program (conceptual — shows push/pop call pattern):**
```c
#include <stdio.h>
int stack[10], top = -1;
void push(int x) { stack[++top] = x; }
int pop() { return stack[top--]; }
int main() { push(5); push(10); printf("%d\n", pop()); return 0; }
```

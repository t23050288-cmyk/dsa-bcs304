# 5. Linked Stacks and Linked Queues

Covers: "Explain Linked Stacks and Queues operations", "implement a stack of
integers using a Singly Linked List".

---

## 5.1 Linked Stack

**Definition:** A stack implemented using a linked list instead of an array —
push and pop happen at the FRONT of the list (the head end), because that end
gives O(1) insertion and deletion with no traversal.

### Points
1. `top` pointer = head of the linked list.
2. **push:** insert a new node at the front, exactly like `insertFront`.
3. **pop:** delete the front node, exactly like `deleteFront`.
4. **Empty condition:** `top == NULL`. **Full condition:** none! (memory is
   taken from the heap — the stack is limited only by available RAM).
5. Advantage over array stack: no fixed size, no overflow until memory runs
   out.
6. Same as array stack: still LIFO — the last pushed node is the first popped.

### Diagram
```
push 10, push 20, push 30:

top -> [30|*] -> [20|*] -> [10|NULL]
        |
     pushed last, popped first (LIFO)

pop removes 30: top -> [20|*] -> [10|NULL]
```

### Easiest Program (`programs/LinkedStack.c`) — compiled & verified
```c
#include <stdio.h>
#include <stdlib.h>
typedef struct node { int data; struct node *link; } Node;
Node *top = NULL;

void push(int v) {
    Node *n = malloc(sizeof(Node));
    n->data = v; n->link = top;
    top = n;
}
int pop(void) {
    Node *t = top; int v;
    if (top == NULL) { printf("Stack EMPTY\n"); return -1; }
    v = top->data; top = top->link; free(t);
    return v;
}
void display(void) {
    Node *t = top;
    while (t) { printf("%d -> ", t->data); t = t->link; }
    printf("NULL (top)\n");
}
int main() {
    push(10); push(20); push(30);
    display();
    printf("popped = %d\n", pop());
    display();
    return 0;
}
```
**Verified output:**
```
30 -> 20 -> 10 -> NULL (top)
popped = 30
20 -> 10 -> NULL (top)
```

---

## 5.2 Linked Queue

**Definition:** A queue implemented using a linked list — insertion at the
REAR, deletion at the FRONT, both O(1) using two pointers.

### Points
1. Keep two pointers: `front` and `rear`.
2. **insert (enqueue):** add the node at the rear end (like insertEnd but
   done in O(1) because rear is remembered — no traversal!).
3. **delete (dequeue):** remove the front node (like deleteFront).
4. **Empty:** `front == NULL` (then rear is also set to NULL).
5. Advantage over array queue: NO false-overflow problem at all — a linked
   queue never needs the circular trick, because there is no fixed array.
6. Full condition: none (limited only by heap memory).

### Diagram
```
front -> [10|*] -> [20|*] -> [30|NULL] <- rear
  ^ delete here                     insert here ^
```

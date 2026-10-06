# 3. Singly Linked Lists (SLL) and Chains

Covers: "What is a linked list?", "different types of linked lists with neat
diagram", "structure definition for SLL", "representing chains in C",
"insert at beginning / end", "delete at front / end", "display".

---

## 3.1 Definition

**Definition:** A linked list is a linear collection of elements called
**nodes**, where each node has a **data part** and a **pointer (link) part**
that stores the address of the NEXT node. The nodes are stored at
non-contiguous (scattered) memory locations and are connected only by the
links.

### Points
1. The entry point of the list is a pointer called **head** (or first), which
   stores the address of the first node.
2. The last node's link is **NULL**, which marks the end of the list.
3. Unlike an array, a linked list does NOT need continuous memory.
4. Size can grow and shrink at **run time** (using `malloc`/`free`) — no need
   to fix the size in advance.
5. Sequential access only: to reach node 5 you must travel through nodes 1-4
   (no direct index access like arrays).
6. Advantage over array: insertion and deletion do NOT require shifting
   elements — only pointers change.
7. Disadvantage: extra memory for the link field, and no O(1) random access.

### Diagram (chain of 3 nodes)
```
head           [10 | *-]-->[20 | *-]-->[30 | NULL]
 |                |            |           |
 └-> 1000         1000         1050        1100   (example addresses)
```

---

## 3.2 Types of Linked Lists

1. **Singly linked list (SLL)** — each node has ONE link, pointing to the
   next node. Can be travelled in one direction only.
2. **Doubly linked list (DLL)** — each node has TWO links: `prev` and `next`.
   Can be travelled in both directions.
3. **Circular linked list** — like an SLL, but the LAST node points back to
   the FIRST node instead of NULL (no NULL end at all).

### Diagram (all three types)
```
SLL:      [10|*]-->[20|*]-->[30|NULL]

DLL:      NULL<-[10]<->[20]<->[30]->NULL
                prev|next  prev|next

CLL:      ┌──────────────────────────┐
          └>[10|*]-->[20|*]-->[30|*]-┘   (last node points back to first)
```

---

## 3.3 Representing Chains in C (the 3 requirements)

**Points (what C needs to build a chain):**
1. A way to **define the node structure** — a self-referential structure.
2. A way to **create new nodes** — the `malloc()` function.
3. A way to **remove nodes no longer needed** — the `free()` function.

### Structure Definition (must-know by heart)
```c
typedef struct node {
    int data;              /* the information field */
    struct node *link;     /* pointer to the next node (self-referential) */
} Node;
```

### Node Creation
```c
Node *n = (Node *)malloc(sizeof(Node));
n->data = 10;
n->link = NULL;
```

---

## 3.4 Basic SLL Operations (with functions)

### (i) Insert a node at the BEGINNING — O(1)
```c
void insertFront(int v) {
    Node *n = malloc(sizeof(Node));
    n->data = v;
    n->link = head;   /* new node points to old first node */
    head = n;         /* head now points to new node */
}
```
Before: `head -> [20] -> NULL`  After insert 10: `head -> [10] -> [20] -> NULL`

### (ii) Insert a node at the END — must travel to the last node
```c
void insertEnd(int v) {
    Node *n = malloc(sizeof(Node)), *t = head;
    n->data = v; n->link = NULL;
    if (head == NULL) { head = n; return; }  /* empty list */
    while (t->link != NULL) t = t->link;     /* go to last node */
    t->link = n;
}
```

### (iii) Delete a node at the FRONT — O(1)
```c
void deleteFront(void) {
    Node *t = head;
    if (head == NULL) { printf("List empty\n"); return; }
    printf("Deleted %d\n", head->data);
    head = head->link;   /* head moves to second node */
    free(t);
}
```

### (iv) Delete a node at the END
```c
void deleteEnd(void) {
    Node *t = head, *prev = NULL;
    if (head == NULL) { printf("List empty\n"); return; }
    while (t->link != NULL) { prev = t; t = t->link; }
    printf("Deleted %d\n", t->data);
    if (prev == NULL) head = NULL;    /* only one node existed */
    else prev->link = NULL;           /* second-last becomes last */
    free(t);
}
```

### (v) Display the list
```c
void display(void) {
    Node *t = head;
    while (t != NULL) { printf("%d -> ", t->data); t = t->link; }
    printf("NULL\n");
}
```

### Easiest Program (`programs/SLLBasicOps.c`) — compiled & verified
Full program with all 4 operations + display.
**Verified output:**
```
10 -> 20 -> 30 -> 40 -> NULL
Deleted 10
Deleted 40
20 -> 30 -> NULL
```

---

## 3.5 Deleting a node whose information field is given

```c
void deleteByValue(int key) {
    Node *t = head, *prev = NULL;
    while (t && t->data != key) { prev = t; t = t->link; }
    if (!t) { printf("%d not found\n", key); return; }
    if (prev == NULL) head = t->link;   /* key was in first node */
    else prev->link = t->link;          /* bypass the node */
    free(t);
}
```
Idea: find the node, then make the PREVIOUS node point to the node AFTER it,
and free the matched node.

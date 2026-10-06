# 8. Doubly Linked List (DLL)

Covers: "define doubly linked list", "advantages of DLL over SLL", "insert a
node at front / rear", "delete a node at front / end", "search a node",
"addition (concatenation) of two DLLs".

---

## 8.1 Definition and Structure

**Definition:** A doubly linked list is a linear data structure in which each
node has TWO links — `prev` pointing to the previous node and `next` pointing
to the next node — so the list can be travelled in BOTH directions.

### Node Structure
```c
typedef struct dnode {
    int data;
    struct dnode *prev, *next;
} DNode;
```

### Diagram
```
NULL <- [prev|10|next] <-> [prev|20|next] <-> [prev|30|next] -> NULL
head = 10's node
```

### Points
1. First node's `prev` is NULL; last node's `next` is NULL.
2. Every node knows BOTH its neighbours — travel is possible in both
   directions.

---

## 8.2 Advantages of DLL over SLL

1. **Traversal in both directions** — SLL only goes forward.
2. **Deletion is faster**: given a node pointer, SLL must still search from
   head for its previous node (O(n)); in a DLL the node already holds `prev`
   (O(1)).
3. **No need to keep track of the previous node** while inserting/deleting.
4. A node can be inserted before a given node easily, without traversal.

**Disadvantage:** each node needs one extra pointer (more memory), and every
operation must maintain BOTH links.

---

## 8.3 Insert a node at the FRONT

```c
void insertFront(DNode **h, int v) {
    DNode *n = malloc(sizeof(DNode));
    n->data = v; n->prev = NULL; n->next = *h;
    if (*h) (*h)->prev = n;    /* old first node's prev points back */
    *h = n;
}
```
**Diagram:**
```
BEFORE:  head -> [10] <-> [20]
insert 5:
         head -> [5] <-> [10] <-> [20]
         (5->next = 10, 10->prev = 5, head = 5)
```

## 8.4 Insert a node at the REAR (end)

```c
void insertRear(DNode **h, int v) {
    DNode *n = malloc(sizeof(DNode)), *t = *h;
    n->data = v; n->next = NULL;
    if (*h == NULL) { n->prev = NULL; *h = n; return; }
    while (t->next) t = t->next;    /* go to last node */
    t->next = n; n->prev = t;
}
```

## 8.5 Delete a node at the FRONT

```c
void deleteFront(DNode **h) {
    DNode *t = *h;
    if (*h == NULL) { printf("List empty\n"); return; }
    printf("Deleted %d\n", (*h)->data);
    *h = (*h)->next;
    if (*h) (*h)->prev = NULL;    /* new first has no prev */
    free(t);
}
```

## 8.6 Delete a node at the END

```c
void deleteRear(DNode **h) {
    DNode *t = *h;
    if (*h == NULL) { printf("List empty\n"); return; }
    while (t->next) t = t->next;    /* go to last node */
    printf("Deleted %d\n", t->data);
    if (t->prev == NULL) *h = NULL; /* only node in list */
    else t->prev->next = NULL;      /* second-last becomes last */
    free(t);
}
```

## 8.7 Search a node with a given key

```c
void search(DNode *h, int key) {
    int pos = 1;
    while (h) {
        if (h->data == key) { printf("Found %d at position %d\n", key, pos); return; }
        h = h->next; pos++;
    }
    printf("%d not found\n", key);
}
```

## 8.8 Concatenation of two DLLs

```c
void concatenate(void) {
    DNode *t = head;
    if (!head) { head = head2; return; }
    while (t->next) t = t->next;   /* last node of list 1 */
    t->next = head2;
    if (head2) head2->prev = t;    /* join backwards too! */
}
```
**Diagram:**
```
BEFORE:  [10] <-> [20]      [100] <-> [200]
AFTER:   [10] <-> [20] <-> [100] <-> [200]
                  20->next=100, 100->prev=20  (BOTH links updated)
```

### Easiest Program (`programs/DLLBasicOps.c`) — compiled & verified
Covers insert front/rear, delete front/rear, search, concatenate.
**Verified output:**
```
10 <-> 20 <-> 30 <-> NULL
Found 20 at position 2
Deleted 10
Deleted 30
20 <-> NULL
20 <-> 100 <-> 200 <-> NULL
```

### Circular Doubly Linked List (extra point)
A circular DLL connects the last node's `next` to the head AND the head's
`prev` to the last node — no NULL ends, travel wraps around in both
directions. Insert/delete logic is the same idea with wrap-around links.

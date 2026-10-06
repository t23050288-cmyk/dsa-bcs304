# 9. Circular Linked List (CLL)

Covers: "inserting at the front of a circular list", "finding the length of
a circular list", "circular doubly linked list".

---

## 9.1 Definition

**Definition:** A circular linked list is a singly linked list in which the
LAST node's link does NOT contain NULL — it points back to the FIRST node,
so the chain forms a ring. There is no end marker in the list.

### Points
1. Any node can be a starting point — travelling the whole list brings you
   back where you started.
2. Useful for round-robin applications: CPU scheduling, multiplayer turn
   games, media playlist repeat.
3. Slightly more care in loops: must STOP when you come back to the starting
   node (not when you hit NULL).

### Diagram
```
        ┌───────────────────────────────┐
        └--> [10|*] --> [20|*] --> [30|*]-┘
       head                              (last node's link = first node)
```

---

## 9.2 Insert a node at the FRONT

```c
void insertFront(int v) {
    Node *n = malloc(sizeof(Node)), *t = head;
    n->data = v;
    if (head == NULL) { n->link = n; head = n; return; }  /* single node ring */
    while (t->link != head) t = t->link;   /* find the LAST node */
    n->link = head;                        /* new node points to old first */
    t->link = n;                           /* last node points to new node */
    head = n;                              /* new node becomes first */
}
```

**Key idea (write in exam):** the LAST node must also be updated, because it
has to point to the new first node — this is the extra step compared to a
normal SLL insertFront.

### Diagram
```
BEFORE:   ┌--> [10] --> [20] ---┐
          └---------------------┘   (head at 10)
insert 5: ┌--> [5] --> [10] --> [20]-┐
          └--------------------------┘  (head at 5, 20 now points to 5)
```

## 9.3 Finding the Length (number of nodes)

```c
int count(void) {
    int c = 0;
    Node *t = head;
    if (head == NULL) return 0;
    do {              /* do-while: runs once even for the head itself */
        c++;
        t = t->link;
    } while (t != head);   /* stop when we circle back to head */
    return c;
}
```
**Key idea:** use a **do-while** loop so the head node is counted, and stop
when the pointer comes back to head — not NULL.

### Easiest Program (`programs/CircularLinkedList.c`) — compiled & verified
**Verified output:**
```
30 -> 20 -> 10 -> (back to head)
Number of nodes = 3
```

---

## 9.4 Circular representation of polynomials (connecting topic)

Polynomials are often stored as circular lists with a header node — see file
`06-Polynomials-Linked-List.md` — the ring makes erasing the whole polynomial
possible in fixed time.

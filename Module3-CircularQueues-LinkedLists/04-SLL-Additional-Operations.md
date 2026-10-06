# 4. Additional SLL Operations: Search, Invert, Concatenate

Covers: "Additional list operations", "search an element in SLL",
"inverting singly linked list", "concatenating two singly linked lists".

---

## 4.1 Search an element in the SLL

```c
void search(int key) {
    Node *t = head; int pos = 1;
    while (t != NULL) {
        if (t->data == key) {
            printf("Found %d at position %d\n", key, pos);
            return;
        }
        t = t->link; pos++;
    }
    printf("%d not found\n", key);
}
```
**Points:** travel node by node from head; compare each node's data with the
key; report the position when found.

---

## 4.2 Inverting (Reversing) the SLL

**Definition:** Reversing the direction of all the links so that the last node
becomes the first.

### Algorithm (the classic 3-pointer method)
```
prev = NULL, cur = head
while cur != NULL:
    next = cur->link     /* save the next node */
    cur->link = prev     /* reverse this node's link */
    prev = cur           /* move prev forward */
    cur = next           /* move cur forward  */
head = prev              /* prev ends at the old last node = new head */
```

### Diagram
```
BEFORE:  head -> [10] -> [20] -> [30] -> NULL
STEP:    each node's arrow gets flipped one by one
AFTER:   head -> [30] -> [20] -> [10] -> NULL
```

### Function
```c
void invert(void) {
    Node *prev = NULL, *cur = head, *next;
    while (cur) {
        next = cur->link;
        cur->link = prev;
        prev = cur;
        cur = next;
    }
    head = prev;
}
```

---

## 4.3 Concatenating two SLLs

**Definition:** Joining the END of the first list to the START of the second
list, producing one combined list.

### Algorithm
```
1. If list1 is empty -> result = list2. Stop.
2. Travel list1 to its last node (where link == NULL).
3. Make that last node's link point to the HEAD of list2.
```

### Function
```c
void concatenate(void) {
    Node *t = head;                 /* head = first list, head2 = second */
    if (head == NULL) { head = head2; return; }
    while (t->link != NULL) t = t->link;
    t->link = head2;
}
```

### Diagram
```
BEFORE:  head ->[10]->[20]->NULL     head2 ->[100]->[200]->NULL
AFTER:   head ->[10]->[20]->[100]->[200]->NULL
```

### Easiest Program (`programs/SLLAdditionalOps.c`) — compiled & verified
Covers search, invert, concatenate and delete-by-value together.
**Verified output:**
```
10 -> 20 -> 30 -> NULL
Found 20 at position 2
30 -> 20 -> 10 -> NULL          <- after invert
30 -> 20 -> 10 -> 100 -> 200 -> NULL   <- after concatenate
Deleted node with value 20
30 -> 10 -> 100 -> 200 -> NULL
```

---

## 4.4 Insert/Delete at the END of SLL (very common exam question)

Already covered in file 03 (`insertEnd` and `deleteEnd`) — for the exam
remember the two edge cases:
1. **insertEnd on an empty list:** `head == NULL`, so the new node directly
   becomes the head.
2. **deleteEnd with only one node:** `prev` stays NULL, so head becomes NULL.

# 1. Introduction to Data Structures, Classification & Operations

Covers: "What is data structure?", "Define Data Structures", classification with
diagram, "primitive operations that can be performed", "explain all operations of
data structures".

---

## 1.1 What is a Data Structure?

**Definition:** A data structure is the logical or mathematical model of a particular
organization of data — it represents the relationships that exist between individual
data elements, not just the elements themselves.

**Points:**
1. A data structure is a way of organizing data that considers both the elements
   stored **and** their relationship to each other.
2. Choice of a data structure depends on two things:
   - It must be rich enough in structure to mirror real-world relationships in the data.
   - It must be simple enough that the data can be processed effectively whenever needed.
3. Related terms: **Data** (values), **Data item** (a single unit of value — group
   item if divisible into sub-items, e.g. Name → first/middle/last; elementary item if
   not divisible, e.g. SSN).
4. **Entity**: something with attributes/properties that can be assigned values (e.g.
   attributes: Name, Age; values: "Rohland", 34).
5. **Field**: a single elementary unit of information representing one attribute.
6. **Record**: the collection of field values of one entity.
7. **File**: the collection of records of all entities in an entity set.
8. Files can have **fixed-length records** (same data items, same space each) or
   **variable-length records** (records vary in length, e.g. student records with
   different numbers of courses).

---

## 1.2 Classification of Data Structures

**Definition:** Data structures are broadly divided into **Primitive** and
**Non-Primitive** categories.

### Diagram
```
                         ┌──────────► Void
                         │
              ┌─Primitive├──────────► Character
              │          │
              │          ├──────────► Integer
              │          │
Data          │          ├──────────► Float
Structures ───┤          │
              │          └──────────► Double
              │
              │              ┌─Linear────► Arrays
              │              │        ├──► Structures
              └─Non-Primitive┤        ├──► Stacks
                             │        ├──► Queues
                             │        └──► Linked Lists
                             │
                             └─Non-Linear─► Trees
                                        └──► Graphs
```

### Full Explanation — Primitive Data Structures

**Primitive data structures** are the basic data types that a machine can directly
operate on. Each one can hold only a **single value** and cannot be divided further.

1. **Integer (int)** — stores whole numbers (no decimal point).
   Example: `int age = 21;` Takes 2 or 4 bytes.
2. **Float (float)** — stores real numbers WITH a decimal point.
   Example: `float price = 99.75;` Takes 4 bytes, about 6 digits accuracy.
3. **Double (double)** — same as float but with double accuracy.
   Example: `double pi = 3.141592653589;` Takes 8 bytes. Used when high precision
   is needed.
4. **Character (char)** — stores ONE letter, digit or symbol inside single quotes.
   Example: `char grade = 'A';` Takes 1 byte.
5. **Void** — means "no value / no type". Used for functions that return nothing,
   e.g. `void display() { ... }`.
6. **Pointer** — a special variable that stores the ADDRESS of another variable.
   Example: `int x = 10; int *p = &x;`

### Full Explanation — Non-Primitive Data Structures

**Non-primitive data structures** are derived from primitive types. They store
**many values together** and define how the values are related to each other.
They are divided into **Linear** and **Non-Linear**.

**A) Linear Data Structures** — elements are arranged in a sequence, one after
another. Each element has exactly one element before it and one after it
(except the first and last).

1. **Array** — a collection of SAME-type elements stored one after another in
   continuous memory locations. Any element is accessed directly by its index.
   Example: `int marks[5] = {90, 80, 85, 70, 95};` — `marks[0]` is 90,
   `marks[1]` is 80, and so on. Size is fixed at creation.
2. **Structure** — a collection of DIFFERENT-type data items grouped under one
   name. Example: a student structure having name (char), age (int) and marks
   (float) together.
3. **Stack** — a LIFO (Last-In First-Out) list. Both insertion (push) and
   deletion (pop) happen at ONE end only, called the top. Real example: a stack
   of plates in a canteen — the last plate kept is taken out first. Used for:
   undo feature, function calls, expression conversion.
4. **Queue** — a FIFO (First-In First-Out) list. Insertion happens at the REAR,
   deletion at the FRONT. Real example: a line of people at a ticket counter —
   the first person to join is served first. Used for: printer job scheduling,
   CPU scheduling.
5. **Linked List** — a collection of nodes, where each node has a data part and
   a pointer part. The pointer stores the address of the NEXT node, so the
   elements need NOT be in continuous memory. Size grows or shrinks at run time.
   Example: `struct node { int data; struct node *next; };`

Note: a linear data structure can be stored in memory in TWO ways — using
**arrays** (continuous locations) or using **linked lists** (connected by
pointers).

**B) Non-Linear Data Structures** — elements are NOT arranged in a sequence.
One element can be connected to MANY elements, showing hierarchical
(parent-child type) relationships.

1. **Tree** — a hierarchical structure starting from one ROOT node at the top.
   Every node (except the root) has exactly ONE parent but can have many
   children. Real examples: a family tree, the folder structure of a computer
   (C:\ → Users → Documents), an organization chart.
2. **Graph** — a collection of VERTICES (points) connected by EDGES (lines).
   Any vertex can connect to any other vertex — no hierarchy. Real examples:
   Google Maps (cities = vertices, roads = edges), a social network (people =
   vertices, friendships = edges).

### Summary Table

| Category | Types | How elements are arranged |
|---|---|---|
| Primitive | int, float, double, char, void, pointer | Single value only |
| Non-Primitive, Linear | Array, Structure, Stack, Queue, Linked List | Sequence, one after another |
| Non-Primitive, Non-Linear | Tree, Graph | Hierarchy or network |

### Program (illustrates primitive vs non-primitive in C)
```c
#include <stdio.h>
int main() {
    int a = 10;             /* primitive: integer */
    char c = 'A';           /* primitive: character */
    float f = 3.14;         /* primitive: float */

    int arr[5] = {1,2,3,4,5}; /* non-primitive, linear: array */

    printf("int=%d char=%c float=%.2f array[2]=%d\n", a, c, f, arr[2]);
    return 0;
}
```

---

## 1.3 Operations on Data Structures

**Definition:** Data structure operations are the standard set of actions that can be
performed on any data structure to create, use, and manage the data within it.

**Points (the 7 primitive operations):**
1. **Create** — reserves memory for the program elements; may happen at compile-time
   or run-time.
2. **Destroy** — releases the memory space allocated for the data structure.
3. **Selection** — accessing a particular data item within the structure.
4. **Updating** — modifying/updating the data in the structure.
5. **Searching** — finding whether a desired data item is present in the structure.
6. **Sorting** — arranging all data items in a particular order (ascending/descending).
7. **Merging** — combining the data items of two different sorted lists into one list.

### Program (demonstrates create, update, search, sort on an array)
```c
#include <stdio.h>
#define SIZE 5

int main() {
    int arr[SIZE] = {40, 10, 30, 20, 50};   /* Create */
    int i, j, temp, key = 30, found = -1;

    arr[2] = 35;                             /* Updating: index 2 changed */

    for (i = 0; i < SIZE; i++) {             /* Searching for key */
        if (arr[i] == key) { found = i; break; }
    }
    printf("Search result for %d: %s\n", key, found != -1 ? "Found" : "Not found");

    for (i = 0; i < SIZE - 1; i++)           /* Sorting (bubble sort) */
        for (j = 0; j < SIZE - 1 - i; j++)
            if (arr[j] > arr[j + 1]) {
                temp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = temp;
            }

    printf("Sorted array: ");
    for (i = 0; i < SIZE; i++) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
```

**Smallest Program (search only):**
```c
#include <stdio.h>
int main() { int a[]={4,8,15,16},i,idx=-1; for(i=0;i<4;i++) if(a[i]==15){idx=i;break;} printf("%d\n",idx); return 0; }
```

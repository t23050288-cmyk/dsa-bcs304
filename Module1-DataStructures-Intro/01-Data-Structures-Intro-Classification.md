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

### Points
1. **Primitive Data Structures** — basic types directly operated on by machine
   instructions; cannot be divided further ("simple data types"). Examples:
   Integer, Float, Character, Pointer.
2. **Non-Primitive Data Structures** — derived from primitive types; emphasize
   structuring a group of homogeneous or heterogeneous data items. Examples:
   Arrays, Lists, Files, Graphs, Trees.
3. Non-primitive types are further split into:
   - **Linear Data Structure** — elements form a sequence/linear list. Two ways to
     represent this in memory:
     a) Sequential memory locations → called **Arrays**.
     b) Pointers/links between elements → called **Linked Lists**.
     Examples: Arrays, Queues, Stacks, Linked Lists.
   - **Non-Linear Data Structure** — data is *not* arranged in sequence; represents
     hierarchical relationships between elements. Insertion/deletion is not linear.
     Examples: Trees, Graphs.

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

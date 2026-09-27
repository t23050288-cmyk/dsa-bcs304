# BCS304 — June/July 2024 Supplementary Exam
## Module 1: Introduction to Data Structures, Arrays, Structures & Sparse Matrices

---

## Q.1 a) Define Data Structures. [4]

### Definition
A data structure is the logical or mathematical model of a particular organization
of data — it represents the relationships that exist between individual data
elements, not just the elements themselves.

### Points
1. A way of organizing data considering both elements stored **and** their
   relationship to each other.
2. Related terms: **Data** (values), **Data item** (single unit of value —
   *group item* if divisible into sub-items, e.g. Name; *elementary item* if not,
   e.g. SSN).
3. **Entity**: something with attributes/properties assigned values.
4. **Field** → **Record** (collection of field values of one entity) → **File**
   (collection of records of all entities).
5. Files can have **fixed-length** or **variable-length** records.

### Smallest Program
```c
#include <stdio.h>
int main() { int arr[3]={1,2,3}; printf("%d\n", arr[1]); return 0; }
```

---

## Q.1 b) Explain the classification of Data Structures with example. [10]

### Definition
Data structures are broadly divided into **Primitive** and **Non-Primitive** categories.

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
1. **Primitive** — basic types directly operated on by machine instructions;
   cannot be divided further. Examples: Integer, Float, Character, Pointer.
2. **Non-Primitive** — derived from primitives; structure groups of homogeneous
   or heterogeneous data. Examples: Arrays, Lists, Files, Graphs, Trees.
3. Non-primitive splits into:
   - **Linear** — elements form a sequence. Represented via **Arrays**
     (sequential memory) or **Linked Lists** (pointers/links). Examples: Arrays,
     Queues, Stacks, Linked Lists.
   - **Non-Linear** — data represents hierarchical relationships, not sequential.
     Examples: Trees, Graphs.

### Easiest Program
```c
#include <stdio.h>
int main() {
    int a = 10;               /* primitive: integer */
    char c = 'A';              /* primitive: character */
    float f = 3.14;            /* primitive: float */
    int arr[5] = {1,2,3,4,5};   /* non-primitive, linear: array */
    printf("int=%d char=%c float=%.2f array[2]=%d\n", a, c, f, arr[2]);
    return 0;
}
```

---

## Q.1 c) Explain all operations of Data Structures. [6]

### Definition
Data structure operations are the standard set of actions performed on any data
structure to create, use, and manage the data within it.

### Points (the 7 operations)
1. **Create** — reserves memory (compile-time or run-time).
2. **Destroy** — releases allocated memory.
3. **Selection** — accessing a particular data item.
4. **Updating** — modifying data in the structure.
5. **Searching** — finding whether a desired item is present.
6. **Sorting** — arranging items in a particular order.
7. **Merging** — combining two sorted lists into one.

### Program (create, update, search, sort)
```c
#include <stdio.h>
#define SIZE 5

int main() {
    int arr[SIZE] = {40, 10, 30, 20, 50};
    int i, j, temp, key = 30, found = -1;

    arr[2] = 35;

    for (i = 0; i < SIZE; i++) if (arr[i] == key) { found = i; break; }
    printf("Search result: %s\n", found != -1 ? "Found" : "Not found");

    for (i = 0; i < SIZE - 1; i++)
        for (j = 0; j < SIZE - 1 - i; j++)
            if (arr[j] > arr[j + 1]) { temp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = temp; }

    printf("Sorted: ");
    for (i = 0; i < SIZE; i++) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
```

---

## Q.2 a) Explain any five string handling functions supported by 'C' with syntax and example. [10]

> ⚠️ **Syllabus flag**: Not explicitly named in the new 2025-scheme syllabus for
> Module 1 — verify examinability with your professor.

### Definition
A string in C is a sequence of characters stored as a character array, terminated
by the null character `\0`. String handling functions perform operations like
comparing, joining, copying, or reversing strings.

### 5 Common Built-in Functions

| Function | Syntax | Description |
|---|---|---|
| `strcpy` | `strcpy(dest, src)` | Copies `src` into `dest` |
| `strcat` | `strcat(dest, src)` | Appends `src` to the end of `dest` |
| `strcmp` | `strcmp(str1, str2)` | Compares two strings; returns 0 if equal |
| `strlen` | `strlen(s)` | Returns the length of string `s` |
| `strrev` | `strrev(s)` | Reverses string `s` in place (non-standard on some compilers) |

### Easiest Program
```c
#include <stdio.h>
#include <string.h>

int main() {
    char s1[50] = "Hello";
    char s2[] = "World";

    printf("strlen(s1) = %lu\n", strlen(s1));
    printf("strcmp(s1,s2) = %d\n", strcmp(s1, s2));

    strcat(s1, s2);
    printf("After strcat: %s\n", s1);

    char s3[50];
    strcpy(s3, s1);
    printf("After strcpy into s3: %s\n", s3);

    return 0;
}
```

**Smallest Program:**
```c
#include <stdio.h>
#include <string.h>
int main() { char s[]="hi"; printf("%lu\n", strlen(s)); return 0; }
```

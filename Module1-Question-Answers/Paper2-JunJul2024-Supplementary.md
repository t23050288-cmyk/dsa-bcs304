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

### The 5 String Functions — Full Explanation

**1. strlen() — String Length**
Counts how many characters are in a string (NOT counting the `\0` at the end).
- **Syntax:** `int len = strlen(string);`
- **Example:** `strlen("Hello")` returns **5**. "Hello" has 5 characters.

**2. strcpy() — String Copy**
Copies one string into another, character by character, including the ending
`\0`. The destination array must be big enough to hold the copied string.
- **Syntax:** `strcpy(destination, source);`
- **Example:** if `char s2[20];` then `strcpy(s2, "Hello");` makes `s2` become
  `"Hello"`.

**3. strcat() — String Concatenate (Join)**
Joins (appends) the second string at the END of the first string. The first
string's `\0` gets overwritten and the result ends with one `\0`.
- **Syntax:** `strcat(string1, string2);`
- **Example:** if `char s1[20] = "Good";` then `strcat(s1, "Morning");` makes
  `s1` become `"GoodMorning"`.

**4. strcmp() — String Compare**
Compares two strings character by character (by their ASCII values).
- Returns **0** if both strings are exactly equal.
- Returns a **negative** value if string1 comes BEFORE string2 in the
  dictionary.
- Returns a **positive** value if string1 comes AFTER string2.
- **Syntax:** `int result = strcmp(string1, string2);`
- **Example:** `strcmp("apple", "ball")` returns negative ('a' < 'b'), and
  `strcmp("apple", "apple")` returns 0.

**5. strrev() — String Reverse**
Reverses a string in place (the same variable holds the reversed result).
- **Syntax:** `strrev(string);`
- **Example:** if `char s[] = "hello";` then `strrev(s);` makes `s` become
  `"olleh"`. (Works in Turbo C; not part of the standard C library on all
  compilers.)

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

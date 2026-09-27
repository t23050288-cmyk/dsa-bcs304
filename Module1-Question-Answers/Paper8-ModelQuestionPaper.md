# BCS304 — Model Question Paper (2023-24 CBCS Scheme)
## Module 1: Introduction to Data Structures, Arrays, Structures & Sparse Matrices

---

## Q.01 a) Define data structures. With a neat diagram, explain the classification of data structures with examples. [5]

### Definition
A data structure is the logical or mathematical model of a particular organization
of data — representing relationships between data elements.

### Classification Diagram
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
1. **Primitive** — Integer, Float, Character, Pointer.
2. **Non-Primitive Linear** — Arrays, Stacks, Queues, Linked Lists.
3. **Non-Primitive Non-Linear** — Trees, Graphs.

---

## Q.01 b) What do you mean by pattern matching? Outline the KMP algorithm and illustrate it. [8]

> ⚠️ **Syllabus flag**: Not explicitly named in the new 2025-scheme syllabus for
> Module 1 — verify examinability with your professor.

### Definition
Pattern matching finds whether/where a **pattern** occurs within a **text**.

### KMP Failure Function Example (`pat = abcabcacab`)

| j | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
|---|---|---|---|---|---|---|---|---|---|---|
| pat | a | b | c | a | b | c | a | c | a | b |
| f | -1 | -1 | -1 | 0 | 1 | 2 | 3 | -1 | 0 | 1 |

### Program (`programs/KMPPatternMatch.c`)
```c
#include <stdio.h>
#include <string.h>
int failure[100];
void computeFailure(char *pat) {
    int n = strlen(pat);
    failure[0] = -1;
    for (int j = 1; j < n; j++) {
        int i = failure[j - 1];
        while (pat[j] != pat[i + 1] && i >= 0) i = failure[i];
        failure[j] = (pat[j] == pat[i + 1]) ? i + 1 : -1;
    }
}
int pmatch(char *text, char *pat) {
    int i = 0, j = 0, lenT = strlen(text), lenP = strlen(pat);
    computeFailure(pat);
    while (i < lenT && j < lenP) {
        if (text[i] == pat[j]) { i++; j++; }
        else if (j == 0) i++;
        else j = failure[j - 1] + 1;
    }
    return (j == lenP) ? (i - lenP) : -1;
}
int main() {
    int pos = pmatch("abxabcabcaby", "abcaby");
    printf(pos != -1 ? "Found at %d\n" : "Not found\n", pos);
    return 0;
}
```

---

## Q.02 a) Explain in brief the different functions of dynamic memory allocation. [5]

### Definition
Dynamic Memory Allocation reserves memory at **run-time**, on the **heap**.

### The 4 Functions
1. `malloc(size)` — allocate, uninitialized.
2. `calloc(n, size)` — allocate n blocks, zero-initialized.
3. `realloc(ptr, newsize)` — resize existing block.
4. `free(ptr)` — deallocate.

### Program (`programs/DynamicMemoryDemo.c`)
```c
#include <stdio.h>
#include <stdlib.h>
int main() {
    int *p = (int*) malloc(sizeof(int)); *p = 5;
    int *arr = (int*) calloc(3, sizeof(int));
    arr = (int*) realloc(arr, 6 * sizeof(int));
    printf("malloc=%d, calloc[0]=%d, realloc done\n", *p, arr[0]);
    free(p); free(arr);
    return 0;
}
```

---

## Q.02 b) Write functions in C (without built-in functions): (i) Compare two strings (ii) Concatenate two strings (iii) Reverse a string. [8]

> ⚠️ **Syllabus flag**: Not explicitly named in the new 2025-scheme syllabus for
> Module 1 — verify examinability with your professor.

### Points
1. **Compare**: walk both strings char by char; return 0 if all match and both
   end together, else the difference of the first mismatched chars.
2. **Concatenate**: find the end (`\0`) of the first string, then copy the second
   string's characters starting there.
3. **Reverse**: swap characters from both ends inward.

### Program (`programs/StringFunctions.c`)
```c
#include <stdio.h>

int myStrcmp(char *s1, char *s2) {
    while (*s1 && *s2) { if (*s1 != *s2) return *s1 - *s2; s1++; s2++; }
    return *s1 - *s2;
}

void myStrcat(char *dest, char *src) {
    while (*dest) dest++;
    while (*src) *dest++ = *src++;
    *dest = '\0';
}

void myStrrev(char *s) {
    int i = 0, j = 0;
    while (s[j] != '\0') j++;
    j--;
    while (i < j) { char t = s[i]; s[i] = s[j]; s[j] = t; i++; j--; }
}

int main() {
    char a[50] = "Hello", b[] = "World";
    printf("Compare: %d\n", myStrcmp(a, b));
    myStrcat(a, b);
    printf("Concat: %s\n", a);
    myStrrev(a);
    printf("Reverse: %s\n", a);
    return 0;
}
```

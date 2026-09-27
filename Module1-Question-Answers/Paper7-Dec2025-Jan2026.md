# BCS304 — Dec 2025/Jan 2026 Exam
## Module 1: Introduction to Data Structures, Arrays, Structures & Sparse Matrices

---

## Q.1 a) Define Data Structure. Explain with neat diagram different types of data structure with examples. What are the primitive operations that can be performed? [10]

### Definition
A data structure is the logical or mathematical model of a particular organization
of data — representing relationships between data elements, not just the elements.

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

### The 7 Primitive Operations
1. **Create** — reserves memory. 2. **Destroy** — releases memory.
3. **Selection** — access a specific item. 4. **Updating** — modify data.
5. **Searching** — find a desired item. 6. **Sorting** — arrange in order.
7. **Merging** — combine two sorted lists.

### Program
```c
#include <stdio.h>
#define SIZE 5
int main() {
    int arr[SIZE] = {40, 10, 30, 20, 50};
    int i, j, temp;
    for (i = 0; i < SIZE - 1; i++)
        for (j = 0; j < SIZE - 1 - i; j++)
            if (arr[j] > arr[j + 1]) { temp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = temp; }
    printf("Sorted: ");
    for (i = 0; i < SIZE; i++) printf("%d ", arr[i]);
    return 0;
}
```

---

## Q.1 b) Define structure and union? Explain how they are different from each other, with suitable example. [5]

### Definitions
**Structure**: collection of data items, each with its own memory space.
**Union**: similar, but all members **share** the same memory space.

### Comparison Table

| Basis | Structure | Union |
|---|---|---|
| Memory | Independent per member | Shared/overlapping |
| Size | Sum of all members | Size of largest member |
| Active members | All at once | One at a time |

### Program (`programs/StructVsUnion.c`)
```c
#include <stdio.h>
struct StructExample { int i; float f; char c; };
union UnionExample { int i; float f; char c; };
int main() {
    struct StructExample s; union UnionExample u;
    s.i = 10; s.f = 3.14; s.c = 'A';
    printf("Struct: i=%d f=%.2f c=%c (all valid)\n", s.i, s.f, s.c);
    u.i = 10;
    printf("Union i=%d\n", u.i);
    u.f = 3.14;
    printf("Union after f set: f=%.2f (i now garbage)\n", u.f);
    return 0;
}
```

---

## Q.1 c) What do you mean by pattern matching? Outline KMP pattern matching algorithm. [5]

> ⚠️ **Syllabus flag**: Not explicitly named in the new 2025-scheme syllabus for
> Module 1 — verify examinability with your professor.

### Definition
Pattern matching finds whether/where a **pattern** occurs within a **text**. KMP
does this in **O(n+m)** time using a precomputed failure function, avoiding
re-checking already-matched characters.

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

# Module 1 — All Definitions Cheat Sheet (Easy to Understand & Tell to Ma'am)

> Each concept: **simple definition → key points → syntax (if applicable)**
> Read this once before the exam and you can explain any term confidently.

---

## 1. Data Structure

**What it is:** The logical/mathematical model of how data items are organized and
related to each other — not just the elements, but how they connect.

**Points:**
- Two categories: **Primitive** (Integer, Float, Character, Pointer) and
  **Non-Primitive** (Arrays, Lists, Trees, Graphs).
- Non-primitive splits into **Linear** (sequence-based: arrays, stacks, queues,
  linked lists) and **Non-Linear** (hierarchical: trees, graphs).

---

## 2. The 7 Data Structure Operations

**Easy way to remember:** *Create, Destroy, Select, Update, Search, Sort, Merge.*

1. **Create** — reserve memory (compile-time or run-time)
2. **Destroy** — release memory
3. **Selection** — access a specific item
4. **Updating** — modify data
5. **Searching** — find a desired item
6. **Sorting** — arrange items in order
7. **Merging** — combine two sorted lists into one

---

## 3. Pointer

**What it is:** A special variable that holds the **address** of a memory location.

**Points:**
- Declared as `type* name;`
- `&` gets an address; `*` dereferences (accesses the value at that address).
- Saves memory when reused instead of duplicating the same value many times.

**Syntax:**
```c
int x = 10;
int *p = &x;
printf("%d", *p);  // prints 10
```

---

## 4. Dynamic Memory Allocation

**What it is:** Reserving memory at **run-time** (on the heap) instead of at
compile-time — used when you don't know the size in advance.

**Points:**
- `malloc(size)` — allocates, memory is uninitialized (garbage).
- `calloc(n, size)` — allocates `n` blocks, memory is zero-initialized.
- `realloc(ptr, newsize)` — resizes an existing block.
- `free(ptr)` — releases the memory.
- Always check for `NULL` return (allocation failure).

---

## 5. Static vs Dynamic Memory Allocation

| Basis | Static | Dynamic |
|---|---|---|
| When | Compile-time | Run-time |
| Size | Fixed | Can grow (realloc) |
| Area | Stack | Heap |
| Risk | Wastes memory | Memory leak if not freed |

---

## 6. Dangling Reference

**What it is:** When all pointers to a dynamically allocated block are lost — the
memory is still allocated but now unreachable/unusable.

**Avoid it by:**
- Setting unused pointers to `NULL`.
- Using explicit type casts between pointer types.
- Always defining explicit return types for functions.

---

## 7. Array

**What it is:** A collection of same-type elements in contiguous memory, accessed
by a zero-based index.

**Points:**
- Address of `list[i]` = base address + `i * sizeof(type)`.
- 2D array = "array of arrays"; `x[i][j]` address = `x[i] + j*sizeof(type)`.
- **Dynamically allocated array**: size decided at run-time via `malloc`, instead
  of a fixed compile-time size — avoids wasted memory.

---

## 8. Structure (struct)

**What it is:** A collection of data items where each item is identified by its
own type and name — lets you group **different types** of related data.

**Points:**
- Each member gets its **own** memory space.
- Accessed with the dot operator (`.`) or arrow (`->`) for pointers.
- Can't be compared with `==` — need a custom comparison function.
- Custom type via `typedef`.

**Syntax:**
```c
typedef struct { char name[10]; int age; float salary; } human_being;
```

---

## 9. Union

**What it is:** Like a structure, but all members **share the same memory** — only
one member is "active"/valid at a time.

**Points:**
- Size = size of the **largest** member.
- Setting one field overwrites the others.
- Often paired with a tag field (`enum`) to track which member is active.

---

## 10. Structure vs Union — Easy Table

| Basis | Structure | Union |
|---|---|---|
| Memory | Each member independent | All members overlap |
| Size | Sum of all members | Size of largest member |
| Active fields | All valid at once | Only one at a time |

---

## 11. Self-Referential Structure

**What it is:** A structure that contains a **pointer to another structure of the
same type** as one of its own members — the basis of linked lists.

**Syntax:**
```c
typedef struct list {
    char data;
    struct list *link;   // points to another 'list' node
} list;
```

---

## 12. Polynomial (Array Representation)

**What it is:** A sum of terms `a·xᵉ`, stored either as a dense array (`coef[]`
indexed by exponent) or as a sparse "triple" array of `{coef, expon}` for
non-zero terms only.

**Points:**
- Dense representation wastes space for sparse polynomials (few non-zero terms).
- Sparse/triple representation stores only non-zero terms — better for sparse
  polynomials, costs ~2x space when all terms are non-zero.
- Adding two polynomials with `m` and `n` non-zero terms takes **O(m+n)** time.

---

## 13. Sparse Matrix

**What it is:** A matrix where **most elements are zero**. Storing it as a normal
2D array wastes memory — instead, store only the non-zero elements.

**Points:**
- **Triplet representation**: array of `<row, col, value>` for each non-zero
  element, plus a header triple (`a[0]`) storing total rows, columns, and count.
- **Transpose**: swap row and column for every triple (`a[i][j] → b[j][i]`).

**Syntax:**
```c
typedef struct { int row, col, value; } term;
term a[MAX_TERMS];
```

---

## 14. Pattern Matching ⚠️

> Flagged: not explicitly in the new syllabus for Module 1 — verify with your professor.

**What it is:** Finding whether/where a smaller string (**pattern**) occurs inside
a bigger string (**text**).

**Points:**
- Naive method: check every position — O(n·m), slow.
- **KMP algorithm**: precomputes a **failure function** so it never re-checks
  already-matched characters — runs in **O(n+m)**.
- On a mismatch, KMP jumps to `failure[j-1]+1` instead of restarting from scratch.

---

## 15. String Handling Functions (without built-ins) ⚠️

> Flagged: not explicitly in the new syllabus for Module 1 — verify with your professor.

**Points:**
- **Compare**: walk both strings char by char, return the difference at the
  first mismatch (or 0 if identical).
- **Concatenate**: find the `\0` at the end of the first string, then copy the
  second string's characters starting there.
- **Reverse**: swap characters from both ends moving toward the middle.

---

## Quick Memory Summary (one-liners for ma'am)

| Term | One-line definition |
|---|---|
| Data Structure | Logical model of how data elements relate to each other |
| Primitive vs Non-Primitive | Basic machine types vs derived/structured types |
| Linear vs Non-Linear | Sequential data vs hierarchical data |
| malloc/calloc/realloc/free | Allocate / allocate+zero / resize / release heap memory |
| Static vs Dynamic allocation | Fixed at compile-time vs sized at run-time |
| Array | Same-type elements in contiguous memory, zero-indexed |
| Structure | Group of different-type data, each member own memory |
| Union | Group of different-type data, all members share memory |
| Self-referential structure | A struct with a pointer to another struct of its own type |
| Polynomial | Sum of coefficient×exponent terms, stored as array of terms |
| Sparse Matrix | Matrix with mostly zero elements, stored as non-zero triplets |
| Pattern Matching | Finding a substring (pattern) inside a larger string (text) |

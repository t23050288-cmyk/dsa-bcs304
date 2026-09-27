# 2. Pointers and Dynamic Memory Allocation

Covers: pointer basics, "discuss four dynamic memory allocation functions", static vs
dynamic memory allocation with syntax for malloc/calloc/realloc/free, dangling
references.

---

## 2.1 Pointers

**Definition:** A pointer is a special variable that contains the **address** of a
memory location; the data stored at that location can be accessed through the pointer.

**Points:**
1. Pointers improve performance for repetitive operations (traversing strings,
   lookup tables, trees) — cheaper to copy/dereference a pointer than to copy the
   actual data.
2. General declaration syntax: `type* name;` — `type` is what the pointer is
   pointing to.
3. Initialization: `variable_type *pointer_name = 0;` or `= NULL;`
4. Example: instead of storing 4 copies of `3.1459`, store it once and use 3 pointers
   referencing that single copy — saves memory since a pointer is smaller than a float.
5. The `*` operator dereferences a pointer (accesses the value it points to); `&`
   gets the address of a variable.

**Syntax:**
```c
int x = 10;
int *p;      /* pointer declaration */
p = &x;      /* p now holds address of x */
printf("%d", *p);  /* dereference: prints 10 */
```

---

## 2.2 Dynamic Memory Allocation

**Definition:** Dynamic Memory Allocation is the process of allocating memory space
during **execution/run-time** (as opposed to compile-time), typically used when
storage requirements are unpredictable in advance. Memory is allocated on the **heap**.

**Points:**
1. Used when we cannot reliably determine array/structure size at compile time.
2. Four main memory management functions: `malloc`, `calloc`, `realloc`, `free`.
3. On success, these functions return a pointer to the start of the allocated block;
   on failure, they return `NULL`.
4. `free()` deallocates memory previously allocated by `malloc()` or `calloc()`.
5. Always check the return value against `NULL` before using the pointer — this
   avoids crashes from failed allocations.

### The 4 Functions in Detail

#### 1. malloc() — Memory Allocate
**Syntax:** `ptr = (cast_type*) malloc(byte_size);`
- Allocates a single block of `byte_size` bytes.
- Memory content is **uninitialized** (contains garbage values).
```c
int *p;
p = (int*) malloc(sizeof(int));   /* allocates 4 bytes for one int */
```

#### 2. calloc() — Contiguous Memory Allocate
**Syntax:** `ptr = (cast_type*) calloc(n, size);`
- Allocates `n` blocks, each of `size` bytes (contiguous memory).
- Memory is automatically **initialized to 0** (key difference from `malloc`).
```c
int *p;
p = (int*) calloc(5, sizeof(int));  /* 5 ints, all initialized to 0 */
```

#### 3. realloc() — Resize Memory
**Syntax:** `ptr = realloc(ptr, new_size);`
- Resizes a memory block previously allocated by `malloc()` or `calloc()`.
- If `new_size` < old size: extra bytes at the end are freed.
- If `new_size` > old size: the additional bytes have unspecified values.
```c
p = realloc(p, 10 * sizeof(int));  /* grow block to hold 10 ints */
```

#### 4. free() — Deallocate Memory
**Syntax:** `free(ptr);`
- Releases memory back to the system so it can be reused.
- Must only be called on memory obtained from `malloc`/`calloc`/`realloc`.
```c
free(p);
```

### Points to remember (Macro Style — for clean programs)
```c
#define MALLOC(p,s) \
  if (!((p) = malloc(s))) { \
    printf("insufficient memory"); exit(0); \
  }
```

### Easiest Program (all four functions demonstrated)
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p1, *p2, i;

    p1 = (int*) malloc(sizeof(int));       /* malloc */
    *p1 = 1024;
    printf("malloc: %d\n", *p1);

    p2 = (int*) calloc(5, sizeof(int));    /* calloc, all zero-initialized */
    printf("calloc initial values: ");
    for (i = 0; i < 5; i++) printf("%d ", p2[i]);
    printf("\n");

    p2 = realloc(p2, 10 * sizeof(int));    /* realloc, grow to 10 ints */
    printf("realloc succeeded, new block can hold 10 ints\n");

    free(p1);                               /* free */
    free(p2);
    printf("memory freed\n");
    return 0;
}
```

**Smallest Program:**
```c
#include <stdio.h>
#include <stdlib.h>
int main() { int *p = malloc(sizeof(int)); *p = 5; printf("%d\n", *p); free(p); return 0; }
```

---

## 2.3 Static vs Dynamic Memory Allocation

**Definition:** Static allocation reserves memory at **compile-time** with a fixed
size; dynamic allocation reserves memory at **run-time** with a size decided while
the program executes.

### Comparison Table

| Basis | Static Allocation | Dynamic Allocation |
|---|---|---|
| When allocated | Compile-time | Run-time |
| Size | Fixed, cannot change | Can grow/shrink (via `realloc`) |
| Memory area | Stack | Heap |
| Example | `int arr[10];` | `int *arr = malloc(10*sizeof(int));` |
| Flexibility | Low — size fixed forever | High — size decided as needed |
| Risk | Wastes memory if overestimated | Risk of memory leak if not freed |

**Points:**
1. Static allocation is simpler but wastes memory if you overestimate size, or
   fails if you underestimate it.
2. Dynamic allocation defers the size decision to run-time — allocate exactly what's
   needed based on user input or computed values.
3. Dynamically allocated memory must be explicitly freed with `free()`, or it causes
   a **memory leak**.

### Program (comparing static vs dynamic array)
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int staticArr[5] = {1, 2, 3, 4, 5};    /* static: fixed size at compile time */

    int n;
    printf("Enter size for dynamic array: ");
    scanf("%d", &n);
    int *dynamicArr = (int*) malloc(n * sizeof(int));  /* dynamic: size known at run-time */

    for (int i = 0; i < n; i++) dynamicArr[i] = i + 1;

    printf("Static array: ");
    for (int i = 0; i < 5; i++) printf("%d ", staticArr[i]);
    printf("\nDynamic array: ");
    for (int i = 0; i < n; i++) printf("%d ", dynamicArr[i]);
    printf("\n");

    free(dynamicArr);
    return 0;
}
```

---

## 2.4 Dangling Reference

**Definition:** A dangling reference occurs when all pointers to a dynamically
allocated block of memory are lost — the memory becomes unreachable (and therefore
unusable/"lost") to the program, even though it's still technically allocated.

**Points (avoiding dangerous pointer bugs):**
1. **Set all pointers to `NULL`** when they aren't actually pointing to an object —
   prevents accessing out-of-range or invalid memory.
2. **Use explicit type casts** when converting between pointer types, e.g.
   `pf = (float*) pi;` when casting an `int*` to `float*`.
3. **Always define explicit return types for functions** — since `int` is the
   default type specifier, omitting a return type can accidentally be interpreted
   as a pointer type.
4. A dangling reference is different from a memory leak: leak = memory still
   allocated but no pointer refers to it; dangling pointer = pointer refers to
   memory that has already been freed.

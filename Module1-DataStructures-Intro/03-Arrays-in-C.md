# 3. Arrays in C (Static & Dynamically Allocated)

Covers: array fundamentals, address computation, dynamically allocated 1D/2D arrays.

---

## 3.1 Arrays — Fundamentals

**Definition:** An array is an ordered set of similar (same-type) data items, stored
in consecutive memory locations, where each item can be accessed via the same name
but a different index value.

**Points:**
1. An array is formally a set of `<index, value>` pairs — a mapping from index to value.
2. All elements are the same data type and stored contiguously.
3. Declared as: `int list[5];` — array of 5 integers.
4. The **base address** is the address of the first element, `list[0]`.
5. Address of `list[i]` = `base_address + i * sizeof(int)` — the compiler computes
   this automatically.
6. Arrays in C do **not** have automatic bounds checking — accessing out-of-range
   indices is undefined behavior.

### Syntax
```c
int list[5];              /* array of 5 integers */
int *plist[5];             /* array of 5 pointers to integers */
```

### Program (address of each element)
```c
#include <stdio.h>
void print1(int *ptr, int rows) {
    /* print address and value of each element using a pointer */
    int i;
    printf("Address\t\tContents\n");
    for (i = 0; i < rows; i++)
        printf("%p\t%d\n", (void*)(ptr + i), *(ptr + i));
}

int main() {
    int one[] = {0, 1, 2, 3, 4};
    print1(&one[0], 5);
    return 0;
}
```

**Smallest Program:**
```c
#include <stdio.h>
int main() { int a[]={10,20,30}; printf("%d %d\n", a[1], a[0]+a[2]); return 0; }
```

---

## 3.2 Dynamically Allocated Arrays

**Definition:** Instead of declaring a fixed-size array at compile time, a
dynamically allocated array reserves exactly the memory needed at **run-time**,
based on a size computed or entered while the program runs.

**Points:**
1. Solves the problem of not knowing array size in advance.
2. Uses `malloc()` (or the `MALLOC` macro) to allocate exactly `n * sizeof(type)` bytes.
3. Avoids memory wastage from over-allocating a static array.
4. Must be freed with `free()` when no longer needed.

### 1D Dynamic Array — Syntax & Program
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int i, n, *list;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n < 1) { printf("improper value"); exit(0); }

    list = (int*) malloc(n * sizeof(int));   /* allocate exactly n ints */
    if (list == NULL) { printf("insufficient memory"); exit(1); }

    for (i = 0; i < n; i++) list[i] = i * i;   /* fill with sample data */

    printf("Dynamic array: ");
    for (i = 0; i < n; i++) printf("%d ", list[i]);
    printf("\n");

    free(list);
    return 0;
}
```

---

## 3.3 Two-Dimensional Arrays (Array of Arrays)

**Definition:** A 2D array is represented as a 1D array, where each element itself
holds a pointer/reference to another 1D array — the "array of arrays" model.

**Points:**
1. Declaration: `int x[5][7];` creates a 1D array `x` of length 5, where each element
   is itself a 1D array of length 7.
2. Address of `x[i][j]` = `x[i] + j * sizeof(int)`.
3. For truly **dynamic** 2D arrays, allocate an array of pointers, then allocate
   each row separately.

### Syntax (dynamically creating a 2D array)
```c
int **array;
array = malloc(nrows * sizeof(int*));   /* array of row-pointers */
for (i = 0; i < nrows; i++)
    array[i] = malloc(ncolumns * sizeof(int));  /* allocate each row */
```

### Program (dynamic 2D array, full)
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int nrows = 3, ncolumns = 4, i, j;
    int **array = malloc(nrows * sizeof(int*));
    if (array == NULL) { printf("out of memory\n"); return 1; }

    for (i = 0; i < nrows; i++) {
        array[i] = malloc(ncolumns * sizeof(int));
        if (array[i] == NULL) { printf("out of memory\n"); return 1; }
    }

    for (i = 0; i < nrows; i++)
        for (j = 0; j < ncolumns; j++)
            array[i][j] = i * ncolumns + j;

    for (i = 0; i < nrows; i++) {
        for (j = 0; j < ncolumns; j++) printf("%d\t", array[i][j]);
        printf("\n");
    }

    for (i = 0; i < nrows; i++) free(array[i]);   /* free each row */
    free(array);                                    /* then free the row-pointer array */
    return 0;
}
```

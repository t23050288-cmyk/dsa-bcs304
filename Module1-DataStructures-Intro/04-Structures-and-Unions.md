# 4. Structures and Unions

Covers: "Differentiate between structures and unions with examples for both",
self-referential structures.

---

## 4.1 Structures

**Definition:** A structure (`struct`) is a collection of data items where each item
is identified by its own type and name — it lets related data of **different types**
be grouped under one variable, unlike an array which only holds one type.

**Points:**
1. Declared using the `struct` keyword.
2. Each field ("member") can be a different data type.
3. Members are accessed using the **dot operator** (`.`).
4. Custom structure types can be created with `typedef` for cleaner code.
5. Structures **cannot** be directly compared with `==` — you must write a custom
   function to check field-by-field equality.
6. Structures can be **nested** — a structure can contain another structure as a field.

### Syntax
```c
struct {
    char name[10];
    int age;
    float salary;
} person;

/* Custom type using typedef */
typedef struct {
    char name[10];
    int age;
    float salary;
} human_being;
```

### Program (structure basics)
```c
#include <stdio.h>
#include <string.h>

typedef struct {
    char name[10];
    int age;
    float salary;
} human_being;

int main() {
    human_being person1;
    strcpy(person1.name, "James");
    person1.age = 30;
    person1.salary = 35000;

    printf("Name: %s, Age: %d, Salary: %.2f\n", person1.name, person1.age, person1.salary);
    return 0;
}
```

---

## 4.2 Unions

**Definition:** A union is similar to a structure, but all its fields **share the
same memory space** — only one field is "active" (holds a meaningful value) at any
given time.

**Points:**
1. All members overlap in memory; the union's size = size of its **largest** member.
2. Setting one member overwrites the memory used by the others.
3. Commonly paired with a **tag field** (often an `enum`) to track which member is
   currently active/valid.
4. Saves memory when only one of several possible fields is needed at a time.

### Syntax
```c
typedef struct {
    enum { female, male } sex;
    union {
        int children;
        int beard;
    } u;
} sex_type;
```

---

## 4.3 Structures vs Unions — Key Differences

| Basis | Structure | Union |
|---|---|---|
| Memory | Each member gets its **own** separate space | All members **share** the same space |
| Size | Sum of sizes of all members (+ padding) | Size of the **largest** member only |
| Active members | All members are valid/active simultaneously | Only **one** member is valid at a time |
| Use case | Grouping unrelated data of a record (e.g. Student: name+age+marks) | Saving memory when only one of several types is needed at once |
| Keyword | `struct` | `union` |
| Access | All fields accessible independently | Writing to one field overwrites others |

### Program (struct vs union side by side)
```c
#include <stdio.h>

struct StructExample { int i; float f; char c; };
union UnionExample { int i; float f; char c; };

int main() {
    struct StructExample s;
    union UnionExample u;

    printf("Size of struct: %lu bytes\n", sizeof(s));  /* sum of all members (+padding) */
    printf("Size of union : %lu bytes\n", sizeof(u));   /* size of largest member only */

    s.i = 10; s.f = 3.14; s.c = 'A';   /* all three fields hold valid, independent values */
    printf("Struct: i=%d f=%.2f c=%c (all still valid)\n", s.i, s.f, s.c);

    u.i = 10;
    printf("Union after setting i: i=%d\n", u.i);
    u.f = 3.14;                          /* overwrites the memory used by i */
    printf("Union after setting f: f=%.2f (i is now garbage: %d)\n", u.f, u.i);

    return 0;
}
```

**Smallest Program:**
```c
#include <stdio.h>
union U { int i; float f; };
int main() { union U u; u.i = 5; printf("%d\n", u.i); u.f = 2.5; printf("%.1f\n", u.f); return 0; }
```

---

## 4.4 Self-Referential Structures

**Definition:** A self-referential structure is a structure that contains, as one of
its own members, a **pointer to another structure of the same type**. This is the
foundation of linked lists, trees, and other linked data structures.

**Points:**
1. Requires dynamic storage management (`malloc`/`free`) to explicitly get and
   release memory for each node.
2. The pointer field is often named `link` or `next`.
3. Each structure instance ("node") points to the next node, chaining them together.
4. The last node's pointer is set to `NULL` to mark the end of the chain.

### Syntax
```c
typedef struct list {
    char data;
    struct list *link;   /* pointer to another structure of the SAME type */
} list;
```

### Easiest Program (with suitable example — chaining 3 nodes)
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    char data;
    struct list *link;
} list;

int main() {
    list *item1 = (list*) malloc(sizeof(list));
    list *item2 = (list*) malloc(sizeof(list));
    list *item3 = (list*) malloc(sizeof(list));

    item1->data = 'a'; item2->data = 'b'; item3->data = 'c';
    item1->link = item2;    /* item1 points to item2 */
    item2->link = item3;    /* item2 points to item3 */
    item3->link = NULL;     /* item3 is the last node */

    list *p = item1;
    printf("Chain: ");
    while (p != NULL) {
        printf("%c -> ", p->data);
        p = p->link;
    }
    printf("NULL\n");

    free(item1); free(item2); free(item3);
    return 0;
}
```

**Smallest Program:**
```c
#include <stdio.h>
struct N { int data; struct N *next; };
int main() { struct N a = {1, NULL}, b = {2, &a}; printf("%d %d\n", b.data, b.next->data); return 0; }
```

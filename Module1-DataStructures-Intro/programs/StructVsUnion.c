/* Differentiate structures and unions with examples for both.
   Answers: "Differentiate between structures and unions with examples for both" */
#include <stdio.h>

struct StructExample { int i; float f; char c; };
union UnionExample { int i; float f; char c; };

int main() {
    struct StructExample s;
    union UnionExample u;

    printf("Size of struct: %lu bytes (sum of all members)\n", sizeof(s));
    printf("Size of union : %lu bytes (size of largest member only)\n", sizeof(u));

    s.i = 10; s.f = 3.14; s.c = 'A';
    printf("Struct: i=%d f=%.2f c=%c (all fields independently valid)\n", s.i, s.f, s.c);

    u.i = 10;
    printf("Union after setting i: i=%d\n", u.i);
    u.f = 3.14;   /* overwrites the memory used by i */
    printf("Union after setting f: f=%.2f (i is now garbage: %d)\n", u.f, u.i);

    return 0;
}

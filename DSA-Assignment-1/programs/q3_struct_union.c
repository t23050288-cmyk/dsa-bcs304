#include <stdio.h>
struct Student { int id; float marks; char grade; };
union Data { int i; float f; char c; };
int main() {
    struct Student s = {1, 85.5, 'A'};
    union Data d;
    printf("size of struct = %zu\n", sizeof(struct Student));
    printf("size of union  = %zu\n", sizeof(union Data));
    d.i = 10;
    printf("d.i = %d\n", d.i);
    d.f = 3.5;
    printf("d.f = %.1f\n", d.f);
    printf("%d %.1f %c\n", s.id, s.marks, s.grade);
    return 0;
}

/* String handling functions WITHOUT built-ins: compare, concatenate, reverse.
   ⚠️ Flagged topic — verify examinability with your professor.
   Answers: "Write functions in C (without built-in functions): compare/concatenate/reverse" */
#include <stdio.h>

/* (i) Compare two strings */
int myStrcmp(char *s1, char *s2) {
    while (*s1 && *s2) {
        if (*s1 != *s2) return *s1 - *s2;
        s1++; s2++;
    }
    return *s1 - *s2;
}

/* (ii) Concatenate two strings (dest must have enough space) */
void myStrcat(char *dest, char *src) {
    while (*dest) dest++;
    while (*src) *dest++ = *src++;
    *dest = '\0';
}

/* (iii) Reverse a string in place */
void myStrrev(char *s) {
    int i = 0, j = 0;
    while (s[j] != '\0') j++;
    j--;
    while (i < j) {
        char temp = s[i];
        s[i] = s[j];
        s[j] = temp;
        i++; j--;
    }
}

int main() {
    char a[50] = "Hello", b[] = "World";

    printf("Compare 'Hello' and 'World': %d\n", myStrcmp(a, b));

    myStrcat(a, b);
    printf("After concatenate: %s\n", a);

    myStrrev(a);
    printf("After reverse: %s\n", a);

    return 0;
}

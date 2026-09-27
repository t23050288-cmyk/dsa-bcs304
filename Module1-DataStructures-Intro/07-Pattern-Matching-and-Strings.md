# 7. ⚠️ Flagged Topics: Pattern Matching (KMP) & String Handling Functions

> **Syllabus flag:** These topics show up repeatedly in previous-year BCS304 papers,
> but are **not explicitly named** in the new 5-module 2025-scheme syllabus for
> Module 1. They were part of the *old* syllabus. Included here because PYQs keep
> asking them — **please verify with your professor** whether they're still
> examinable before over-investing revision time here.

---

## 7.1 Pattern Matching & the KMP Algorithm

Covers: "What do you mean by pattern matching? Outline Knuth Morris Pratt (KMP)
pattern matching algorithm", "Write KMP pattern matching algorithm and apply the
same to search the pattern in the text".

### Definition
Pattern matching is the process of finding whether (and where) a smaller string
(the **pattern**) occurs within a larger string (the **text**).

### Points
1. The simplest method checks every position in the text, comparing character by
   character — computing time **O(n·m)** where `n` = pattern length, `m` = text
   length (slow for large inputs).
2. C's built-in `strstr(text, pat)` does simple pattern matching, but returns `NULL`
   if `pat` isn't found, or a pointer to the first match if it is.
3. **Knuth-Morris-Pratt (KMP)** is a smarter algorithm that avoids re-checking
   characters it has already matched, by precomputing a **failure function** `f(j)`
   for the pattern.
4. **Failure function definition:** for pattern `p = p₀p₁...pₙ₋₁`,
   `f(j)` = the largest `i < j` such that the first `i+1` characters of the pattern
   equal the `i+1` characters ending at position `j` — or `-1` if no such `i` exists.
5. When a mismatch occurs at pattern position `j`, instead of restarting from
   scratch, KMP jumps to position `f(j-1)+1` in the pattern — skipping unnecessary
   re-comparisons.
6. Overall computing time for KMP is **O(n + m)** — much faster than the naive method.

### Example (failure function for `pat = abcabcacab`)

| j | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
|---|---|---|---|---|---|---|---|---|---|---|
| pat | a | b | c | a | b | c | a | c | a | b |
| f | -1 | -1 | -1 | 0 | 1 | 2 | 3 | -1 | 0 | 1 |

### Easiest Program (KMP pattern matching, C)
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
        if (pat[j] == pat[i + 1]) failure[j] = i + 1;
        else failure[j] = -1;
    }
}

int pmatch(char *text, char *pat) {
    int i = 0, j = 0;
    int lenT = strlen(text), lenP = strlen(pat);
    computeFailure(pat);
    while (i < lenT && j < lenP) {
        if (text[i] == pat[j]) { i++; j++; }
        else if (j == 0) i++;
        else j = failure[j - 1] + 1;
    }
    return (j == lenP) ? (i - lenP) : -1;
}

int main() {
    char text[] = "abxabcabcaby";
    char pat[]  = "abcaby";
    int pos = pmatch(text, pat);
    if (pos != -1) printf("Pattern found at index %d\n", pos);
    else printf("Pattern not found\n");
    return 0;
}
```

**Smallest Program (using built-in `strstr` instead of writing KMP):**
```c
#include <stdio.h>
#include <string.h>
int main() { char *s="hello world", *p="world"; char *r=strstr(s,p); printf(r ? "found at %ld\n" : "not found\n", r ? r-s : 0); return 0; }
```

---

## 7.2 String Handling Functions (Without Built-ins)

Covers: "Write functions in C (without built-in functions): (i) Compare two strings
(ii) Concatenate two strings (iii) Reverse a string", "Explain any five string
handling functions supported by 'C' with syntax and example".

### Definition
A string in C is a sequence of characters stored as a character array, terminated by
the null character `\0`. String handling functions perform operations like
comparing, joining, copying, or reversing strings.

### Common Built-in String Functions (for the "explain 5 functions" question)

| Function | Syntax | Description |
|---|---|---|
| `strcpy` | `strcpy(dest, src)` | Copies `src` into `dest` |
| `strcat` | `strcat(dest, src)` | Appends `src` to the end of `dest` |
| `strcmp` | `strcmp(str1, str2)` | Compares two strings; returns 0 if equal |
| `strlen` | `strlen(s)` | Returns the length of string `s` |
| `strrev` | `strrev(s)` (non-standard, `<string.h>` on some compilers) | Reverses string `s` in place |

### Custom Functions (Without Built-ins)

**Points:**
1. **Compare**: walk both strings character by character; return 0 if all match and
   both end together, else return the difference of the first mismatched characters
   (or a code like -1/1).
2. **Concatenate**: find the end of the first string (`\0`), then copy the second
   string's characters starting from there.
3. **Reverse**: swap characters from both ends moving inward until the middle is
   reached.

### Easiest Program (all 3 functions, without built-ins)
```c
#include <stdio.h>

/* (i) Compare two strings */
int myStrcmp(char *s1, char *s2) {
    while (*s1 && *s2) {
        if (*s1 != *s2) return *s1 - *s2;
        s1++; s2++;
    }
    return *s1 - *s2;   /* handles different lengths too */
}

/* (ii) Concatenate two strings (dest must have enough space) */
void myStrcat(char *dest, char *src) {
    while (*dest) dest++;         /* move to end of dest */
    while (*src) *dest++ = *src++; /* copy src onto the end */
    *dest = '\0';
}

/* (iii) Reverse a string in place */
void myStrrev(char *s) {
    int i = 0, j = 0;
    while (s[j] != '\0') j++;    /* find length */
    j--;
    while (i < j) {
        char temp = s[i]; s[i] = s[j]; s[j] = temp;
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
```

**Smallest Program (reverse only):**
```c
#include <stdio.h>
int main() { char s[]="abcd"; int i=0,j=3; while(i<j){char t=s[i];s[i]=s[j];s[j]=t;i++;j--;} printf("%s\n", s); return 0; }
```

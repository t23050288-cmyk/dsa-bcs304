/* Knuth-Morris-Pratt (KMP) pattern matching algorithm.
   ⚠️ Flagged topic — verify examinability with your professor.
   Answers: "What do you mean by pattern matching? Outline KMP pattern matching algorithm",
            "Write KMP pattern matching algorithm and apply the same to search the pattern" */
#include <stdio.h>
#include <string.h>

int failure[100];

/* compute the failure function for the pattern */
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

/* returns index of first match, or -1 if not found */
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

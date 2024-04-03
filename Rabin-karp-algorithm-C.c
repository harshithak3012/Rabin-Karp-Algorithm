#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define d 256

void search(const char *pat, const char *txt, int q) {
    int M = strlen(pat);
    int N = strlen(txt);
    int i, j;
    int p = 0;
    int t = 0;
    int h = 1;
    int found = 0;

    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    for (i = 0; i < M; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    for (i = 0; i <= N - M; i++) {
        if (p == t) {
            for (j = 0; j < M; j++) {
                if (txt[i + j] != pat[j]) {
                    break;
                }
            }
            if (j == M) {
                printf("Pattern found at index %d\n", i + 1);
                found = 1;
            }
        }
        if (i < N - M) {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;
            if (t < 0)
                t = (t + q);
        }
    }

    if (!found) {
        printf("Pattern not found.\n");
    }
}

int main() {
    FILE *inputFile;
    char txt[1000], pat[1000];
    int q = INT_MAX;
    int numTestCases = 4;
    char filename[] = "input.txt";

    inputFile = fopen(filename, "r");
    if (inputFile != NULL) {
        for (int testCase = 0; testCase < numTestCases; ++testCase) {
            fgets(txt, sizeof(txt), inputFile);
            txt[strcspn(txt, "\n")] = 0; 
            fgets(pat, sizeof(pat), inputFile);
            pat[strcspn(pat, "\n")] = 0;
			printf("\n"); 
            printf("Output of testcase %d:\n", testCase + 1);
            search(pat, txt, q);
        }
        fclose(inputFile);
    } else {
        printf("Unable to open file.\n");
    }

    return 0;
}

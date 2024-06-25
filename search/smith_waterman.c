#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "smith_waterman.h"

// Maximum of three values
int max(int a, int b, int c) {
    if (a >= b && a >= c)
        return a;
    else if (b >= a && b >= c)
        return b;
    else
        return c;
}

// Maximum of four values
int max4(int a, int b, int c, int d) {
    return max(max(a, b, c), d, 0);
}

// Smith-Waterman algorithm
void smith_waterman(const char *seq1, const char *seq2) {
    int len1 = strlen(seq1);
    int len2 = strlen(seq2);

    // Allocate memory for the scoring matrix
    int **score = (int **)malloc((len1 + 1) * sizeof(int *));
    for (int i = 0; i <= len1; i++) {
        score[i] = (int *)malloc((len2 + 1) * sizeof(int));
    }

    // Initialize scoring matrix
    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            score[i][j] = 0;
        }
    }

    // Fill scoring matrix
    int max_score = 0;
    int max_i = 0, max_j = 0;
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            int match = (seq1[i - 1] == seq2[j - 1]) ? MATCH : MISMATCH;
            score[i][j] = max4(score[i - 1][j - 1] + match, score[i - 1][j] + GAP, score[i][j - 1] + GAP, 0);
            if (score[i][j] > max_score) {
                max_score = score[i][j];
                max_i = i;
                max_j = j;
            }
        }
    }

    // Traceback
    char aligned1[len1 + len2 + 1];
    char aligned2[len1 + len2 + 1];
    int align_idx = 0;

    int i = max_i;
    int j = max_j;
    while (i > 0 && j > 0 && score[i][j] > 0) {
        if (score[i][j] == score[i - 1][j - 1] + ((seq1[i - 1] == seq2[j - 1]) ? MATCH : MISMATCH)) {
            aligned1[align_idx] = seq1[i - 1];
            aligned2[align_idx] = seq2[j - 1];
            i--;
            j--;
        } else if (score[i][j] == score[i - 1][j] + GAP) {
            aligned1[align_idx] = seq1[i - 1];
            aligned2[align_idx] = '-';
            i--;
        } else {
            aligned1[align_idx] = '-';
            aligned2[align_idx] = seq2[j - 1];
            j--;
        }
        align_idx++;
    }

    // Reverse the aligned sequences
    aligned1[align_idx] = '\0';
    aligned2[align_idx] = '\0';
    for (int k = 0; k < align_idx / 2; k++) {
        char temp = aligned1[k];
        aligned1[k] = aligned1[align_idx - 1 - k];
        aligned1[align_idx - 1 - k] = temp;
        temp = aligned2[k];
        aligned2[k] = aligned2[align_idx - 1 - k];
        aligned2[align_idx - 1 - k] = temp;
    }

    // Print the aligned sequences
    printf("Alignment 1: %s\n", aligned1);
    printf("Alignment 2: %s\n", aligned2);

    // Free memory
    for (int i = 0; i <= len1; i++) {
        free(score[i]);
    }
    free(score);
}
#ifndef SMITH_WATERMAN_H
#define SMITH_WATERMAN_H

// Scoring system
#define MATCH 2
#define MISMATCH -1
#define GAP -1

// Function prototypes
int max(int a, int b, int c);
int max4(int a, int b, int c, int d);
void smith_waterman(const char *seq1, const char *seq2);

#endif // SMITH_WATERMAN_H

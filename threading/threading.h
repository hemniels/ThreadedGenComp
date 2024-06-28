#ifndef THREADING_H
#define THREADING_H

#include <pthread.h>

// Struktur für Thread-Daten
typedef struct {
    int thread_id;
    int num_threads;
    int seq1_len;
    int seq2_len;
    int **score_matrix;
    char *seq1;
    char *seq2;
} thread_data_t;

// Funktion zur Initialisierung und Start der Threads
void parallel_smith_waterman(char *seq1, char *seq2, int num_threads);

#endif // THREADING_H

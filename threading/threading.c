#include "threading.h"
#include <stdlib.h>
#include <string.h>

#define MATCH 2
#define MISMATCH -1
#define GAP -1

// Funktion zur Berechnung der Score-Matrix
void* calculate_scores(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    int rows_per_thread = (data->seq1_len + data->num_threads - 1) / data->num_threads;
    int start_row = data->thread_id * rows_per_thread + 1;
    int end_row = (data->thread_id + 1) * rows_per_thread;

    if (end_row > data->seq1_len) end_row = data->seq1_len;

    for (int i = start_row; i <= end_row; i++) {
        for (int j = 1; j <= data->seq2_len; j++) {
            int match = (data->seq1[i-1] == data->seq2[j-1]) ? MATCH : MISMATCH;
            int score_diag = data->score_matrix[i-1][j-1] + match;
            int score_up = data->score_matrix[i-1][j] + GAP;
            int score_left = data->score_matrix[i][j-1] + GAP;
            data->score_matrix[i][j] = score_diag > 0 ? score_diag : 0;
            if (score_up > data->score_matrix[i][j]) data->score_matrix[i][j] = score_up;
            if (score_left > data->score_matrix[i][j]) data->score_matrix[i][j] = score_left;
        }
    }

    pthread_exit(NULL);
}

// Hauptfunktion zur Initialisierung und Start der Threads
void parallel_smith_waterman(char *seq1, char *seq2, int num_threads) {
    int seq1_len = strlen(seq1);
    int seq2_len = strlen(seq2);

    int **score_matrix = malloc((seq1_len + 1) * sizeof(int *));
    for (int i = 0; i <= seq1_len; i++) {
        score_matrix[i] = malloc((seq2_len + 1) * sizeof(int));
        memset(score_matrix[i], 0, (seq2_len + 1) * sizeof(int));
    }

    pthread_t threads[num_threads];
    thread_data_t thread_data[num_threads];

    for (int i = 0; i < num_threads; i++) {
        thread_data[i].thread_id = i;
        thread_data[i].num_threads = num_threads;
        thread_data[i].seq1_len = seq1_len;
        thread_data[i].seq2_len = seq2_len;
        thread_data[i].score_matrix = score_matrix;
        thread_data[i].seq1 = seq1;
        thread_data[i].seq2 = seq2;

        pthread_create(&threads[i], NULL, calculate_scores, &thread_data[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    int max_score = 0;
    for (int i = 1; i <= seq1_len; i++) {
        for (int j = 1; j <= seq2_len; j++) {
            if (score_matrix[i][j] > max_score) {
                max_score = score_matrix[i][j];
            }
        }
    }

    for (int i = 0; i <= seq1_len; i++) {
        free(score_matrix[i]);
    }
    free(score_matrix);

    printf("Maximaler Smith-Waterman-Score: %d\n", max_score);
}

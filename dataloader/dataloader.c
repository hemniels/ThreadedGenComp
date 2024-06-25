#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataloader.h"

#define BUFFER_SIZE 4096

int load_fasta_file(const char *file_path, Sequence **sequences, int *seq_count) {
    FILE *file = fopen(file_path, "r");
    if (!file) {
        perror("Fehler beim Öffnen der Datei");
        return -1;
    }

    char *buffer = malloc(BUFFER_SIZE);
    char *current_seq = malloc(BUFFER_SIZE * 10);  // Platz für eine längere Sequenz
    size_t current_seq_len = 0;
    Sequence *seq_array = malloc(sizeof(Sequence) * 100);  // Startgröße
    int count = 0;
    int header = 1; // Flag to identify header lines
    char *buffer_end = buffer + BUFFER_SIZE;
    char *start, *end;

    while (1) {
        size_t bytes_read = fread(buffer, 1, BUFFER_SIZE, file);
        if (bytes_read == 0) break;

        start = buffer;
        end = buffer;

        while (end < buffer + bytes_read) {
            if (*end == '>') {
                if (header == 0 && current_seq_len > 0) {
                    // Aktuelle Sequenz speichern
                    seq_array[count - 1].sequence = strndup(current_seq, current_seq_len);
                    current_seq_len = 0;
                }
                // Neue Sequenz starten
                start = end + 1;
                while (*end != '\n' && end < buffer + bytes_read) end++;
                seq_array[count].id = strndup(start, end - start);
                count++;
                header = 1;
                if (count % 100 == 0) {
                    seq_array = realloc(seq_array, sizeof(Sequence) * (count + 100));
                }
            } else if (*end != '\n' && *end != '\r') {
                current_seq[current_seq_len++] = *end;
                header = 0;
            }
            end++;
        }

        // Restliche Pufferinhalte für den nächsten Durchlauf aufbewahren
        size_t remaining = buffer + bytes_read - start;
        memmove(buffer, start, remaining);
    }

    if (current_seq_len > 0) {
        seq_array[count - 1].sequence = strndup(current_seq, current_seq_len);
    }

    free(buffer);
    free(current_seq);
    fclose(file);
    *sequences = seq_array;
    *seq_count = count;
    return 0;
}

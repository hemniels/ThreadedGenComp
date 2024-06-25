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

    while (1) {
        size_t bytes_read = fread(buffer, 1, BUFFER_SIZE, file);
        if (bytes_read == 0) break;

        for (size_t i = 0; i < bytes_read; i++) {
            if (buffer[i] == '>') {
                if (header == 0 && current_seq_len > 0) {
                    // Aktuelle Sequenz speichern
                    seq_array[count - 1].sequence = strdup(current_seq);
                    current_seq_len = 0;
                }
                // Neue Sequenz starten
                size_t id_start = i + 1;
                while (i < bytes_read && buffer[i] != '\n') i++;
                buffer[i] = '\0';
                seq_array[count].id = strdup(&buffer[id_start]);
                count++;
                header = 1;
                if (count % 100 == 0) {
                    seq_array = realloc(seq_array, sizeof(Sequence) * (count + 100));
                }
            } else if (buffer[i] != '\n' && buffer[i] != '\r') {
                current_seq[current_seq_len++] = buffer[i];
                current_seq[current_seq_len] = '\0';
                header = 0;
            }
        }
    }

    if (current_seq_len > 0) {
        seq_array[count - 1].sequence = strdup(current_seq);
    }

    free(buffer);
    free(current_seq);
    fclose(file);
    *sequences = seq_array;
    *seq_count = count;
    return 0;
}

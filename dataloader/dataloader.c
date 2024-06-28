#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataloader.h"

void init_sequence_list(SequenceList* list, int initial_capacity) {
    list->sequences = (char**)malloc(initial_capacity * sizeof(char*));
    list->count = 0;
    list->capacity = initial_capacity;
}

void expand_sequence_list(SequenceList* list) {
    int new_capacity = list->capacity * 2;
    list->sequences = (char**)realloc(list->sequences, new_capacity * sizeof(char*));
    list->capacity = new_capacity;
}

void add_sequence(SequenceList* list, const char* sequence) {
    if (list->count == list->capacity) {
        expand_sequence_list(list);
    }
    list->sequences[list->count] = strdup(sequence);
    list->count++;
}

void load_sequences(const char* filename, SequenceList* list) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Fehler beim Öffnen der Datei");
        exit(EXIT_FAILURE);
    }

    // Dateigröße ermitteln
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Dateiinhalt in einen Puffer lesen
    char* buffer = (char*)malloc(file_size + 1);
    if (!buffer) {
        perror("Fehler beim Allozieren des Puffers");
        exit(EXIT_FAILURE);
    }
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';  // Nullterminator hinzufügen

    fclose(file);

    // Sequenzen parsen
    char* line = buffer;
    char sequence[MAX_LINE_LENGTH * 10] = "";  // Annahme: eine Sequenz kann mehrere Zeilen umfassen
    int sequence_length = 0;

    while (*line) {
        char* next_line = strchr(line, '\n');
        if (next_line) {
            *next_line = '\0';
            next_line++;
        }

        if (line[0] == '>') {  // Header-Zeile
            if (sequence_length > 0) {
                add_sequence(list, sequence);
                sequence[0] = '\0';
                sequence_length = 0;
            }
        } else {  // Sequenz-Zeile
            strcat(sequence, line);
            sequence_length += strlen(line);
        }

        line = next_line;
    }

    // Letzte Sequenz hinzufügen
    if (sequence_length > 0) {
        add_sequence(list, sequence);
    }

    free(buffer);
}

void free_sequence_list(SequenceList* list) {
    for (int i = 0; i < list->count; i++) {
        free(list->sequences[i]);
    }
    free(list->sequences);
}

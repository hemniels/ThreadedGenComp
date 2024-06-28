#ifndef DATALOADER_H
#define DATALOADER_H

#define MAX_LINE_LENGTH 1024

typedef struct {
    char** sequences;
    int count;
    int capacity;
} SequenceList;

void init_sequence_list(SequenceList* list, int initial_capacity);
void expand_sequence_list(SequenceList* list);
void add_sequence(SequenceList* list, const char* sequence);
void load_sequences(const char* filename, SequenceList* list);
void free_sequence_list(SequenceList* list);

#endif // DATALOADER_H

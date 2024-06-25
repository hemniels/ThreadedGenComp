#ifndef DATALOADER_H
#define DATALOADER_H

typedef struct {
    char *id;
    char *sequence;
} Sequence;

int load_fasta_file(const char *file_path, Sequence **sequences, int *seq_count);

#endif // DATALOADER_H

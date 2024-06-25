#include <stdio.h>
#include <stdlib.h>
#include "dataloader.h"

void test_load_fasta_file() {
    const char *file_path = "path/to/your/test.fa";
    Sequence *sequences = NULL;
    int seq_count = 0;

    if (load_fasta_file(file_path, &sequences, &seq_count) != 0) {
        fprintf(stderr, "Fehler beim Laden der FASTA-Datei\n");
        return;
    }

    // Ausgabe einer repräsentativen Probe der gelesenen Daten
    for (int i = 0; i < seq_count; i++) {
        printf("ID: %s\n", sequences[i].id);
        printf("Sequence (erste 60 Zeichen): %.60s\n", sequences[i].sequence);
        if (i >= 9) break;  // Nur die ersten 10 Sequenzen anzeigen
    }

    // Speicher freigeben
    for (int i = 0; i < seq_count; i++) {
        free(sequences[i].id);
        free(sequences[i].sequence);
    }
    free(sequences);
}

int main() {
    test_load_fasta_file();
    return 0;
}

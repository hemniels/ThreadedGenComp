#include <stdio.h>
#include "dataloader.h"

int main() {
    SequenceList list;
    init_sequence_list(&list, 10);  // Starte mit einer Kapazität von 10

    load_sequences("random_sequences_1.txt", &list);

    // Ausgabe der geladenen Sequenzen zur Überprüfung
    for (int i = 0; i < list.count; i++) {
        printf("Sequence %d: %s\n", i + 1, list.sequences[i]);
    }

    free_sequence_list(&list);
    return 0;
}

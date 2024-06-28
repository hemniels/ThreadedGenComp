#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "threading.h"

// Eine einfache Testfunktion, um die parallel_smith_waterman Funktion zu testen
void test_parallel_smith_waterman() {
    char seq1[] = "ACACACTA";
    char seq2[] = "AGCACACA";
    int num_threads = 4;

    printf("Test 1: Sequenz 1: %s, Sequenz 2: %s, Threads: %d\n", seq1, seq2, num_threads);
    parallel_smith_waterman(seq1, seq2, num_threads);

    char seq3[] = "GATTACA";
    char seq4[] = "GCATGCU";
    printf("Test 2: Sequenz 1: %s, Sequenz 2: %s, Threads: %d\n", seq3, seq4, num_threads);
    parallel_smith_waterman(seq3, seq4, num_threads);
}

int main() {
    printf("Starten der Tests für parallel_smith_waterman\n");
    test_parallel_smith_waterman();
    printf("Tests abgeschlossen\n");
    return 0;
}

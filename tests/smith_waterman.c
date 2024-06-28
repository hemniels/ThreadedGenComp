#include <stdio.h>
#include <string.h>

int main() {
    const char *seq1 = "ACACACTA";
    const char *seq2 = "AGCACACA";

    smith_waterman(seq1, seq2);

    return 0;
}
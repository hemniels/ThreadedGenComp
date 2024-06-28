import random
import string

def generate_random_sequence(length):
    return ''.join(random.choices('ACGT', k=length))

def create_fasta_file(filename, num_sequences):
    with open(filename, 'w') as file:
        for i in range(1, num_sequences + 1):
            header = f">Sequence_{i}"
            sequence_length = random.randint(50, 300)  # Zufällige Länge zwischen 50 und 300
            sequence = generate_random_sequence(sequence_length)
            file.write(f"{header}\n{sequence}\n")

# Erstelle zwei FASTA-Dateien mit jeweils 150 zufälligen Sequenzen
create_fasta_file('random_sequences_1.txt', 150)
create_fasta_file('random_sequences_2.txt', 150)

#!/bin/bash

# Setze den Ausführungs- und Ausgabepfad
OUTPUT_DIR="bin"
OUTPUT_FILE="test_dataloader"

# Erstelle das Ausgabe-Verzeichnis, falls es nicht existiert
mkdir -p $OUTPUT_DIR

# Kompilieren der Dateien
gcc -o $OUTPUT_DIR/$OUTPUT_FILE dataloader/dataloader.c tests/test_dataloader.c

# Überprüfen, ob die Kompilierung erfolgreich war
if [ $? -eq 0 ]; then
    echo "Kompilierung erfolgreich."
    echo "Ausführbare Datei: $OUTPUT_DIR/$OUTPUT_FILE"
else
    echo "Kompilierung fehlgeschlagen."
    exit 1
fi

# Ausführen des kompilierten Programms
$OUTPUT_DIR/$OUTPUT_FILE

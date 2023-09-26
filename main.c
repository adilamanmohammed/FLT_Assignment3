#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALPHABET_SIZE 26
#define MAX_STATES 100

// Function to read the DFSM specification from a file
void readDFSMSpecification(FILE *file, char alphabet[], int transition_table[][MAX_ALPHABET_SIZE], int *num_states, int final_states[], int *num_final_states) {
    // Read the input alphabet
    fscanf(file, "%s", alphabet);
    int alphabet_size = strlen(alphabet);

    // Read the number of states
    fscanf(file, "%d", num_states);

    // Read the transition table
    for (int i = 0; i < *num_states; i++) {
        for (int j = 0; j < alphabet_size; j++) {
            fscanf(file, "%d", &transition_table[i][j]);
        }
    }

    // Read the number of final states
    fscanf(file, "%d", num_final_states);

    // Read the final states
    for (int i = 0; i < *num_final_states; i++) {
        fscanf(file, "%d", &final_states[i]);
    }
}

// Function to classify strings into equivalence classes
void classifyStrings(FILE *inputFile, FILE *outputFiles[], char alphabet[], int transition_table[][MAX_ALPHABET_SIZE], int num_states, int final_states[], int num_final_states) {
    char buffer[256]; // Adjust buffer size as needed
    int class_index = 1;

    // Initialize output files
    for (int i = 0; i < num_final_states; i++) {
        char filename[20];
        sprintf(filename, "group_%d.txt", i + 1);
        outputFiles[i] = fopen(filename, "w");
    }

    // Read and classify strings
    while (fgets(buffer, sizeof(buffer), inputFile)) {
        int current_state = 1; // Start state
        int i = 0;

        while (buffer[i] != '\0' && buffer[i] != '\n') {
            char symbol = buffer[i++];
            int symbol_index = strchr(alphabet, symbol) - alphabet;

            if (symbol_index >= 0 && symbol_index < strlen(alphabet)) {
                current_state = transition_table[current_state - 1][symbol_index];
            }
        }

        // Write the string to the appropriate output file
        for (int j = 0; j < num_final_states; j++) {
            if (current_state == final_states[j]) {
                fprintf(outputFiles[j], "%s", buffer);
                break;
            }
        }
    }

    // Close output files
    for (int i = 0; i < num_final_states; i++) {
        fclose(outputFiles[i]);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <DFSM specification file> <input strings file>\n", argv[0]);
        return 1;
    }

    FILE *specFile = fopen(argv[1], "r");
    FILE *inputFile = fopen(argv[2], "r");

    if (specFile == NULL || inputFile == NULL) {
        printf("Error: Unable to open files.\n");
        return 1;
    }

    char alphabet[MAX_ALPHABET_SIZE];
    int transition_table[MAX_STATES][MAX_ALPHABET_SIZE];
    int num_states;
    int final_states[MAX_STATES];
    int num_final_states;

    readDFSMSpecification(specFile, alphabet, transition_table, &num_states, final_states, &num_final_states);

    FILE *outputFiles[num_final_states];
    classifyStrings(inputFile, outputFiles, alphabet, transition_table, num_states, final_states, num_final_states);

    // Close input files
    fclose(specFile);
    fclose(inputFile);

    return 0;
}

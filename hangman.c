#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function to load words from a file
void loadWordsFromFile(const char *filename, char *words[], int *index) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "File not found\n");
        exit(1);
    }

    char word[100];
    while (fscanf(file, "%s", word) != EOF) {
        words[*index] = malloc(strlen(word) + 1); // Allocate memory for each word
        if (words[*index] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            fclose(file);
            exit(1);
        }
        strcpy(words[*index], word); // Copy the word into the array
        (*index)++;
    }

    fclose(file);
}

// Function to choose a random word
void chooseWord(char *words[], int index, char **wordToGuess) {
    srand((unsigned)time(NULL)); // Seed the random number generator
    int randomIndex = rand() % index;
    int length = strlen(words[randomIndex]);
    
    // Allocate memory for the chosen word
    *wordToGuess = malloc((length + 1) * sizeof(char));
    if (*wordToGuess == NULL) {
        fprintf(stderr, "Memory allocation failed for wordToGuess\n");
        exit(1);
    }

    // Copy the selected word into the output parameter
    strcpy(*wordToGuess, words[randomIndex]);
}

// Function to initialize the hidden word with underscores
void initializeHiddenWord(char *hiddenWord, int length) {
    for (int i = 0; i < length; i++) {
        hiddenWord[i] = '_';
    }
    hiddenWord[length] = '\0'; // Null-terminate the string
}

// Function to handle the guessing game
void playGame(char *wordToGuess) {
    int length = strlen(wordToGuess);
    char hiddenWord[length + 1];
    initializeHiddenWord(hiddenWord, length);

    int attempts = 0;
    const int maxAttempts = 6;
    char input[100];

    while (strchr(hiddenWord, '_') != NULL && attempts < maxAttempts) {
        printf("\nWord to guess: ");
        for (int i = 0; i < length; i++) {
            if (hiddenWord[i] == '_') {
                printf("\033[1;31m %c \033[0m", hiddenWord[i]); // Red color for underscores
            } else {
                printf("\033[1;32m %c \033[0m", hiddenWord[i]); // Green color for guessed letters
            }
        }
        printf("\nRemaining attempts: %d\n", maxAttempts - attempts);
        printf("Enter a letter or the whole word: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove newline character

        // Check if the user guessed the whole word
        if (strcmp(input, wordToGuess) == 0) {
            strcpy(hiddenWord, wordToGuess);
            break;
        }

        char letter = input[0];
        int correctGuess = 0;

        // Update hiddenWord if the guessed letter is correct
        for (int i = 0; i < length; i++) {
            if (wordToGuess[i] == letter) {
                hiddenWord[i] = letter;
                correctGuess = 1;
            }
        }

        if (!correctGuess) {
            attempts++;
        }
    }

    printf("\033[1;32m\nThe word was: %s\n", wordToGuess);
    if (strchr(hiddenWord, '_') == NULL) {
        printf("Congratulations! You guessed the word.\033[0m\n");
    } else {
        printf("\033[1;31mGame over. Better luck next time!\033[0m\n");
    }
}

int main() {
    char *words[100];
    int wordCount = 0;

    // Load words from the file
    loadWordsFromFile("words.txt", words, &wordCount);

    // Choose a random word
    char *wordToGuess = NULL;
    chooseWord(words, wordCount, &wordToGuess);

    // Play the guessing game
    playGame(wordToGuess);

    // Free allocated memory
    for (int i = 0; i < wordCount; i++) {
        free(words[i]);
    }
    free(wordToGuess);

    return 0;
}

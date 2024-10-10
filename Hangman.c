#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ATTEMPTS 10
#define WORD_LIST_SIZE 21
#define ALPHABET_SIZE 26

// selects random word from list
const char* choose_word() {
    const char* words[WORD_LIST_SIZE] = {"programming", "studio", "computer", "science", "development", "vision",
                                        "laptop", "convert", "classroom", "project", "tradition", "ceremony", "episode", 
                                        "bright", "degree", "major", "college", "university", "basic", "monkey", "promise"};
    return words[rand() % WORD_LIST_SIZE];
}

// displays current state of word
void display_word(const char* word, char* guessed) {
    for (int i = 0; i < strlen(word); i++) {
        if (guessed[i]) {
            printf("%c ", word[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

int main() {
    srand(time(0)); // random num generator
    const char* word = choose_word();
    int length = strlen(word);
    char guessed[length];  // to track guessed letters
    memset(guessed, 0, sizeof(guessed)); 

    int attempts = MAX_ATTEMPTS;
    char guess;
    int guessed_letters[ALPHABET_SIZE] = {0};

    printf("Welcome to Hangman! You have %d attempts to guess the word.\n", MAX_ATTEMPTS);

    while (attempts > 0) {
        display_word(word, guessed);
        printf("Attempts remaining: %d\n", attempts);
        printf("Enter a letter: ");
        scanf(" %c", &guess);
        
        // convert to lowercase
        if (guess >= 'A' && guess <= 'Z') {
            guess += 'a' - 'A';
        }

        // checks if letter has already been guessed
        if (guess < 'a' || guess > 'z') {
            printf("Invalid input! Please enter a letter from A to Z.\n");
            continue;
        }

        if (guessed_letters[guess - 'a']) {
            printf("You've already guessed the letter '%c'\n", guess);
            continue;
        }

        // marks letter as guessed
        guessed_letters[guess - 'a'] = 1;

        int correct_guess = 0;
        for (int i = 0; i < length; i++) {
            if (word[i] == guess) {
                guessed[i] = 1;  // mark letter as guessed
                correct_guess = 1;
            }
        }

        if (!correct_guess) {
            attempts--;
            printf("Wrong guess! Try again.\n");
        }

        // checks if fully guessed
        int word_guessed = 1;
        for (int i = 0; i < length; i++) {
            if (!guessed[i]) {
                word_guessed = 0;
                break;
            }
        }

        if (word_guessed) {
            printf("Congratulations! You've guessed the word: %s\n", word);
            break;
        }
    }

    if (attempts == 0) {
        printf("Game over! The word was: %s\n", word);
    }
    return 0;
}

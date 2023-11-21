#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define BOARD_SIZE 4

// Function to check if a character is a valid letter (a to z)
int isValidLetter(char letter) {
    return (letter >= 'a' && letter <= 'z');
}

//  Boggle board
void initializeBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    printf("Enter the Boggle board using 16 letters from 'a' to 'z'\n");
    char letter;
    int letterCount = 0;

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            scanf(" %c", &letter);

            // Validate the input
            while (!isValidLetter(letter)) {
                printf("Invalid input. Enter a valid letter from 'a' to 'z': ");
                scanf(" %c", &letter);
            }

            board[i][j] = tolower(letter); // Convert to lowercase in every case
            letterCount++;

            // the total letter count exceeds 16
            if (letterCount > 16) {
                printf("Error: Too many letters. Enter exactly 16 letters.\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    // the total letter count is less than 16
    if (letterCount < 16) {
        printf("Error: Too few letters. Enter exactly 16 letters.\n");
        exit(EXIT_FAILURE);
    }
}

//  print the Boggle board
void printBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    printf("+++++++++++\n");
    for (int i = 0; i < BOARD_SIZE; ++i) {
        printf("| ");
        for (int j = 0; j < BOARD_SIZE; ++j) {
            printf("%c ", board[i][j]);
        }
        printf("|\n");
    }
    printf("+++++++++++\n");
}

// word checking with DFS algorithm
int isWordPresent(char board[BOARD_SIZE][BOARD_SIZE], const char* word,
                  int row, int col, int index, int visited[BOARD_SIZE][BOARD_SIZE]) {
   
    if (word[index] == '\0') {
        return 1;
    }

    // letter matching
    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE &&
        board[row][col] == word[index] && !visited[row][col]) {
        // Mark as visited and make the letter to uppercase
        visited[row][col] = 1;
        board[row][col] = toupper(board[row][col]);

        // check all 8 adjacent cells
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (isWordPresent(board, word, row + i, col + j, index + 1, visited)) {
                    return 1;
                }
            }
        }

        // Mark  as not visited
        visited[row][col] = 0;
        board[row][col] = tolower(board[row][col]);
    }

    return 0;
}

//  check the word on the Boggle board
int isWordOnBoard(char board[BOARD_SIZE][BOARD_SIZE], const char* word) {
    int visited[BOARD_SIZE][BOARD_SIZE] = {{0}};

    //  find the starting letter
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (isWordPresent(board, word, i, j, 0, visited)) {
                return 1;
            }
        }
    }

    return 0;
}

int main() {
    char board[BOARD_SIZE][BOARD_SIZE];

    initializeBoard(board);

    printBoard(board);

    char inputWord[256];

    do {
        printf("Enter a word (or '1' to quit): ");
        scanf("%s", inputWord);

        if (inputWord[0] == '1' && inputWord[1] == '\0') {
            printf("Exiting the program.\n");
            return 0;
        }

        if (isWordOnBoard(board, inputWord)) {
            printf("'%s' is present on the board.\n", inputWord);
            // Show the grid with uppercase letters
            printBoard(board);
            break;  // Exit the loop if the word is found
        } else {
            printf("'%s' is not present on the board. Try a new word.\n", inputWord);
            // Show the grid again
            printBoard(board);
        }

    } while (1);  // Keep, until a valid word

    return 0;
}


#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

char playfair_matrix[SIZE][SIZE] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};

void prepare_text(char *text) {
    int i, j;
    for (i = 0; text[i]; i++) {
        if (text[i] == 'J') {
            text[i] = 'I';
        }
        text[i] = toupper(text[i]);
    }
    for (i = 0; text[i]; i++) {
        if (text[i] == ' ') {
            for (j = i; text[j]; j++) {
                text[j] = text[j + 1];
            }
            i--;
        }
    }
    for (i = 0; text[i]; i += 2) {
        if (text[i] == text[i + 1]) {
            for (j = i + 1; text[j]; j++) {
                text[j] = text[j + 1];
            }
            text[i + 1] = 'X';
        }
    }
    if (strlen(text) % 2 != 0) {
        strcat(text, "X");
    }
}

void find_position(char ch, int *row, int *col) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (playfair_matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encrypt(char *text) {
    int i, row1, col1, row2, col2;
    for (i = 0; i < strlen(text); i += 2) {
        find_position(text[i], &row1, &col1);
        find_position(text[i + 1], &row2, &col2);
        if (row1 == row2) {
            text[i] = playfair_matrix[row1][(col1 + 1) % SIZE];
            text[i + 1] = playfair_matrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            text[i] = playfair_matrix[(row1 + 1) % SIZE][col1];
            text[i + 1] = playfair_matrix[(row2 + 1) % SIZE][col2];
        } else {
            text[i] = playfair_matrix[row1][col2];
            text[i + 1] = playfair_matrix[row2][col1];
        }
    }
}

int main() {
    char text[] = "Must see you over Cadogan West. Coming at once.";
    prepare_text(text);
    encrypt(text);
    printf("Encrypted text: %s\n", text);
    return 0;
}

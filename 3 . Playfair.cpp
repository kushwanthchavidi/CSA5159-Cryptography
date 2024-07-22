#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 5
#define ALPHABET_SIZE 26

void toUpperCase(char* str) {
    while (*str) {
        *str = toupper(*str);
        str++;
    }
}

void removeDuplicates(char* str) {
    char seen[ALPHABET_SIZE] = {0};
    char *src = str, *dst = str;

    while (*src) {
        if (*src >= 'A' && *src <= 'Z') {
            if (!seen[*src - 'A']) {
                seen[*src - 'A'] = 1;
                *dst++ = *src;
            }
        }
        src++;
    }
    *dst = '\0';
}

void fillMatrix(char matrix[MATRIX_SIZE][MATRIX_SIZE], const char* key) {
    char used[ALPHABET_SIZE] = {0};
    int k = 0;
    int i;
    
    for (i = 0; key[i]; i++) {
        char ch = key[i];
        if (ch == 'J') ch = 'I';
        if (ch >= 'A' && ch <= 'Z' && !used[ch - 'A']) {
            used[ch - 'A'] = 1;
            matrix[k / MATRIX_SIZE][k % MATRIX_SIZE] = ch;
            k++;
        }
    }

    for (i = 0; i < ALPHABET_SIZE; i++) {
        char ch = 'A' + i;
        if (ch == 'J') continue;
        if (!used[ch - 'A']) {
            matrix[k / MATRIX_SIZE][k % MATRIX_SIZE] = ch;
            k++;
        }
    }
}

void preprocessText(const char* input, char* output) {
    int j = 0;
    int i;
    for (i = 0; input[i]; i++) {
        char ch = toupper(input[i]);
        if (ch == 'J') ch = 'I';
        if (ch >= 'A' && ch <= 'Z') {
            if (j > 0 && output[j - 1] == ch) {
                output[j++] = 'X'; // Add a filler character if the same letter is repeated
            }
            output[j++] = ch;
        }
    }
    output[j] = '\0';
    if (j % 2 != 0) {
        output[j++] = 'X'; // Add a filler character if length is odd
        output[j] = '\0';
    }
}

void findPosition(char matrix[MATRIX_SIZE][MATRIX_SIZE], char ch, int* row, int* col) {
    int i, j;
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encryptPair(char matrix[MATRIX_SIZE][MATRIX_SIZE], char a, char b, char* encA, char* encB) {
    int rowA, colA, rowB, colB;
    findPosition(matrix, a, &rowA, &colA);
    findPosition(matrix, b, &rowB, &colB);

    if (rowA == rowB) {
        *encA = matrix[rowA][(colA + 1) % MATRIX_SIZE];
        *encB = matrix[rowB][(colB + 1) % MATRIX_SIZE];
    } else if (colA == colB) {
        *encA = matrix[(rowA + 1) % MATRIX_SIZE][colA];
        *encB = matrix[(rowB + 1) % MATRIX_SIZE][colB];
    } else {
        *encA = matrix[rowA][colB];
        *encB = matrix[rowB][colA];
    }
}

void playfairEncrypt(const char* plaintext, const char* key, char* ciphertext) {
    char matrix[MATRIX_SIZE][MATRIX_SIZE];
    char processedText[1024];
    char encA, encB;
    int len;
    int i;

    fillMatrix(matrix, key);
    preprocessText(plaintext, processedText);

    len = strlen(processedText);

    for (i = 0; i < len; i += 2) {
        encryptPair(matrix, processedText[i], processedText[i + 1], &encA, &encB);
        ciphertext[i] = encA;
        ciphertext[i + 1] = encB;
    }
    ciphertext[len] = '\0';
}

int main() {
    char key[100], plaintext[100], ciphertext[100];

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline character

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character

    toUpperCase(key);
    toUpperCase(plaintext);
    playfairEncrypt(plaintext, key, ciphertext);

    printf("Encrypted text: %s\n", ciphertext);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define ALPHABET_SIZE 26
#define MAX_TEXT_SIZE 1000

const double englishFreq[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 0.772, 
    4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 
    2.360, 0.150, 1.974, 0.074
};

void computeFreq(const char *text, double *freq) {
    int count[ALPHABET_SIZE] = {0};
    int length = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            count[toupper(text[i]) - 'A']++;
            length++;
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i] = (length > 0) ? (double)count[i] / length * 100 : 0.0;
    }
}

double scorePlaintext(const char *text) {
    double freq[ALPHABET_SIZE] = {0};
    computeFreq(text, freq);

    double score = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        score += (freq[i] - englishFreq[i]) * (freq[i] - englishFreq[i]);
    }

    return score;
}

void decrypt(const char *ciphertext, char *plaintext, const char *key) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            int index = toupper(ciphertext[i]) - 'A';
            plaintext[i] = key[index];
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int compare(const void *a, const void *b) {
    double diff = *(const double*)a - *(const double*)b;
    return (diff > 0) - (diff < 0);
}

void generateKey(double *cipherFreq, char *key) {
    int map[ALPHABET_SIZE] = {0};
    int used[ALPHABET_SIZE] = {0};

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        double minDiff = 1e9;
        int minIdx = -1;

        for (int j = 0; j < ALPHABET_SIZE; j++) {
            if (!used[j] && fabs(cipherFreq[i] - englishFreq[j]) < minDiff) {
                minDiff = fabs(cipherFreq[i] - englishFreq[j]);
                minIdx = j;
            }
        }

        key[i] = 'A' + minIdx;
        used[minIdx] = 1;
    }
    key[ALPHABET_SIZE] = '\0'; // Null-terminate the key
}

int main() {
    char ciphertext[MAX_TEXT_SIZE];
    char plaintext[MAX_TEXT_SIZE];
    char key[ALPHABET_SIZE + 1];
    double cipherFreq[ALPHABET_SIZE] = {0};

    printf("Enter the ciphertext: ");
    fgets(ciphertext, MAX_TEXT_SIZE, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';

    computeFreq(ciphertext, cipherFreq);
    generateKey(cipherFreq, key);

    printf("Possible key: %s\n", key);

    decrypt(ciphertext, plaintext, key);
    printf("Decrypted text: %s\n", plaintext);

    return 0;
}


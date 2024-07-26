#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_TEXT_SIZE 1000
#define MAX_PLAINTEXTS 10

const double englishFreq[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 0.772, 
    4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 
    2.360, 0.150, 1.974, 0.074
};

void computeFreq(char *text, double *freq) {
    int count[ALPHABET_SIZE] = {0};
    int length = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            count[toupper(text[i]) - 'A']++;
            length++;
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i] = (double)count[i] / length * 100;
    }
}

double scorePlaintext(char *text) {
    double freq[ALPHABET_SIZE] = {0};
    computeFreq(text, freq);

    double score = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        score += (freq[i] - englishFreq[i]) * (freq[i] - englishFreq[i]);
    }

    return score;
}

void decrypt(char *ciphertext, char *plaintext, int shift) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = ((ciphertext[i] - base - shift + ALPHABET_SIZE) % ALPHABET_SIZE) + base;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

typedef struct {
    char text[MAX_TEXT_SIZE];
    double score;
} PlaintextCandidate;

int compare(const void *a, const void *b) {
    double scoreA = ((PlaintextCandidate*)a)->score;
    double scoreB = ((PlaintextCandidate*)b)->score;
    return (scoreA > scoreB) - (scoreA < scoreB);
}

int main() {
    char ciphertext[MAX_TEXT_SIZE];
    char plaintext[MAX_TEXT_SIZE];
    PlaintextCandidate candidates[ALPHABET_SIZE];

    printf("Enter the ciphertext: ");
    fgets(ciphertext, MAX_TEXT_SIZE, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';

    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        decrypt(ciphertext, plaintext, shift);
        candidates[shift].score = scorePlaintext(plaintext);
        strcpy(candidates[shift].text, plaintext);
    }

    qsort(candidates, ALPHABET_SIZE, sizeof(PlaintextCandidate), compare);

    int topN = MAX_PLAINTEXTS;
    printf("Top %d possible plaintexts:\n", topN);
    for (int i = 0; i < topN; i++) {
        printf("%d: %s (Score: %.2f)\n", i + 1, candidates[i].text, candidates[i].score);
    }

    return 0;
}

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MOD 26
#define MATRIX_SIZE 2

void multiplyMatrixVector(int matrix[MATRIX_SIZE][MATRIX_SIZE], int vector[MATRIX_SIZE], int result[MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        result[i] = 0;
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
        result[i] %= MOD;
    }
}

int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 0) {
            return x;
        }
    }
    return -1;
}

void findInverseMatrix(int key[MATRIX_SIZE][MATRIX_SIZE], int inverse[MATRIX_SIZE][MATRIX_SIZE]) {
    int determinant = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % MOD;
    if (determinant < 0) determinant += MOD;

    int invDet = modInverse(determinant, MOD);

    inverse[0][0] = (key[1][1] * invDet) % MOD;
    inverse[0][1] = (-key[0][1] * invDet) % MOD;
    inverse[1][0] = (-key[1][0] * invDet) % MOD;
    inverse[1][1] = (key[0][0] * invDet) % MOD;

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (inverse[i][j] < 0) inverse[i][j] += MOD;
        }
    }
}

void encrypt(char *plaintext, int key[MATRIX_SIZE][MATRIX_SIZE], char *ciphertext) {
    int length = strlen(plaintext);
    for (int i = 0; i < length; i += 2) {
        int vector[MATRIX_SIZE] = {plaintext[i] - 'A', plaintext[i+1] - 'A'};
        int result[MATRIX_SIZE];
        multiplyMatrixVector(key, vector, result);
        ciphertext[i] = result[0] + 'A';
        ciphertext[i+1] = result[1] + 'A';
    }
    ciphertext[length] = '\0';
}

void decrypt(char *ciphertext, int key[MATRIX_SIZE][MATRIX_SIZE], char *plaintext) {
    int inverseKey[MATRIX_SIZE][MATRIX_SIZE];
    findInverseMatrix(key, inverseKey);

    int length = strlen(ciphertext);
    for (int i = 0; i < length; i += 2) {
        int vector[MATRIX_SIZE] = {ciphertext[i] - 'A', ciphertext[i+1] - 'A'};
        int result[MATRIX_SIZE];
        multiplyMatrixVector(inverseKey, vector, result);
        plaintext[i] = result[0] + 'A';
        plaintext[i+1] = result[1] + 'A';
    }
    plaintext[length] = '\0';
}

int main() {
    char plaintext[] = "MEETMEATUSUALPLACEATTENRATHERTHANEIGHTOCLOCK";
    char ciphertext[sizeof(plaintext)];
    char decryptedtext[sizeof(plaintext)];

    int key[MATRIX_SIZE][MATRIX_SIZE] = {
        {9, 4},
        {5, 7}
    };

   
    encrypt(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

   
    decrypt(ciphertext, key, decryptedtext);
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}

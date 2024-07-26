#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_TEXT_SIZE 100
void encrypt(char *plaintext, int *key, char *ciphertext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            int shift = key[i % 13]; 
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = ((plaintext[i] - base + shift) % 26) + base;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[len] = '\0';
}
void decrypt(char *ciphertext, int *key, char *plaintext) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            int shift = key[i % 13]; 
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = ((ciphertext[i] - base - shift + 26) % 26) + base;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[len] = '\0';
}
void findKey(char *ciphertext, char *desired_plaintext, int *key) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i]) && isalpha(desired_plaintext[i])) {
            char cipher_base = isupper(ciphertext[i]) ? 'A' : 'a';
            char plain_base = isupper(desired_plaintext[i]) ? 'A' : 'a';
            key[i % 13] = (ciphertext[i] - cipher_base - (desired_plaintext[i] - plain_base) + 26) % 26;
        }
    }
}
int main() {
    char plaintext[MAX_TEXT_SIZE] = "send more money";
    int key[13] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    char ciphertext[MAX_TEXT_SIZE];
    char decrypted_text[MAX_TEXT_SIZE];
    int new_key[13] = {0};
    char desired_plaintext[MAX_TEXT_SIZE] = "cash not needed";
    encrypt(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);
    decrypt(ciphertext, key, decrypted_text);
    printf("Decrypted Text: %s\n", decrypted_text);
    findKey(ciphertext, desired_plaintext, new_key);
    printf("New Key: ");
    for (int i = 0; i < 13; i++) {
        printf("%d ", new_key[i]);
    }
    printf("\n");
    decrypt(ciphertext, new_key, decrypted_text);
    printf("Decrypted Text with New Key: %s\n", decrypted_text);
    return 0;
}

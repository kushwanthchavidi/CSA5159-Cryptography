#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void generateCipherAlphabet(const char *keyword, char cipherAlphabet[]) {
    int used[ALPHABET_SIZE] = {0};
    int index = 0;
    for (int i = 0; keyword[i] != '\0'; i++) {
        char ch = toupper(keyword[i]);
        if (!used[ch - 'A']) {
            cipherAlphabet[index++] = ch;
            used[ch - 'A'] = 1;
        }
    }
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            cipherAlphabet[index++] = ch;
        }
    }
}

void encryptMessage(const char *message, const char cipherAlphabet[], char *encryptedMessage) {
    for (int i = 0; message[i] != '\0'; i++) {
        char ch = toupper(message[i]);
        if (isalpha(ch)) {
            encryptedMessage[i] = cipherAlphabet[ch - 'A'];
        } else {
            encryptedMessage[i] = ch;
        }
    }
    encryptedMessage[strlen(message)] = '\0';
}

void decryptMessage(const char *encryptedMessage, const char cipherAlphabet[], char *decryptedMessage) {
    char reverseCipherAlphabet[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        reverseCipherAlphabet[cipherAlphabet[i] - 'A'] = 'A' + i;
    }

    for (int i = 0; encryptedMessage[i] != '\0'; i++) {
        char ch = toupper(encryptedMessage[i]);
        if (isalpha(ch)) {
            decryptedMessage[i] = reverseCipherAlphabet[ch - 'A'];
        } else {
            decryptedMessage[i] = ch;
        }
    }
    decryptedMessage[strlen(encryptedMessage)] = '\0';
}

int main() {
    const char keyword[] = "CIPHER";
    char cipherAlphabet[ALPHABET_SIZE];

    generateCipherAlphabet(keyword, cipherAlphabet);

    printf("Cipher alphabet: ");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        printf("%c ", cipherAlphabet[i]);
    }
    printf("\n");

    const char message[] = "HELLO WORLD";
    char encryptedMessage[strlen(message) + 1];
    char decryptedMessage[strlen(message) + 1];

    encryptMessage(message, cipherAlphabet, encryptedMessage);
    printf("Encrypted message: %s\n", encryptedMessage);

    decryptMessage(encryptedMessage, cipherAlphabet, decryptedMessage);
    printf("Decrypted message: %s\n", decryptedMessage);

    return 0;
}

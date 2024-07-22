#include <stdio.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26


bool isCoprimeWith26(int a) {
    return (a % 2 != 0) && (a % 13 != 0);
}
char encryptChar(char ch, int a, int b) {
    if (ch >= 'A' && ch <= 'Z') {
        return ((a * (ch - 'A') + b) % ALPHABET_SIZE) + 'A';
    } else {
        return ch; 
    }
}
char decryptChar(char ch, int a, int b) {
    int i;
    int a_inv = -1;
    if (ch >= 'A' && ch <= 'Z') {
        for (i = 1; i < ALPHABET_SIZE; i++) {
            if ((a * i) % ALPHABET_SIZE == 1) {
                a_inv = i;
                break;
            }
        }
        if (a_inv == -1) {
            printf("No modular inverse found. Decryption not possible.\n");
            return ch;
        }
        return ((a_inv * ((ch - 'A') - b + ALPHABET_SIZE)) % ALPHABET_SIZE) + 'A';
    } else {
        return ch;
    }
}

int main() {
    int a, b;
    char mode;
    char input[100];
    int i;

    printf("Enter key 'a' (must be coprime with 26): ");
    scanf("%d", &a);
    printf("Enter key 'b': ");
    scanf("%d", &b);

    if (!isCoprimeWith26(a)) {
        printf("Error: Key 'a' must be coprime with 26.\n");
        return 1;
    }

    printf("Enter mode (e for encryption, d for decryption): ");
    scanf(" %c", &mode);

    printf("Enter the text (only uppercase letters will be processed): ");
    scanf(" %[^\n]", input);

    if (mode == 'e') {
        printf("Encrypted text: ");
        for (i = 0; input[i] != '\0'; i++) {
            printf("%c", encryptChar(input[i], a, b));
        }
        printf("\n");
    } else if (mode == 'd') {
        printf("Decrypted text: ");
        for (i = 0; input[i] != '\0'; i++) {
            printf("%c", decryptChar(input[i], a, b));
        }
        printf("\n");
    } else {
        printf("Invalid mode selected.\n");
    }

    return 0;
}

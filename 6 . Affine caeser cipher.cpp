#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to find the greatest common divisor
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to find the modular multiplicative inverse
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

// Encryption function
void affineEncrypt(char plaintext[], int a, int b) {
    char ch;
    for (int i = 0; i < strlen(plaintext); i++) {
        ch = plaintext[i];
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            ch = (a * (ch - base) + b) % 26 + base;
        }
        putchar(ch);
    }
    printf("\n");
}

// Decryption function
void affineDecrypt(char ciphertext[], int a, int b) {
    char ch;
    int a_inv = modInverse(a, 26); // Find the modular multiplicative inverse of a
    if (a_inv == -1) {
        printf("Multiplicative inverse of a does not exist. Decryption is not possible.\n");
        return;
    }
    for (int i = 0; i < strlen(ciphertext); i++) {
        ch = ciphertext[i];
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            ch = (a_inv * ((ch - base) - b + 26)) % 26 + base;
        }
        putchar(ch);
    }
    printf("\n");
}

int main() {
    char text[100];
    int a, b;

    printf("Enter the plaintext: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // Remove the newline character

    printf("Enter the value of a (must be coprime with 26): ");
    scanf("%d", &a);
    printf("Enter the value of b: ");
    scanf("%d", &b);

    if (gcd(a, 26) != 1) {
        printf("The value of a is not coprime with 26. Encryption is not possible.\n");
        return 1;
    }

    printf("Encrypted text: ");
    affineEncrypt(text, a, b);

    // Reading ciphertext for decryption
    printf("Enter the ciphertext: ");
    getchar(); // Clear the newline character from the buffer
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // Remove the newline character

    printf("Decrypted text: ");
    affineDecrypt(text, a, b);

    return 0;
}

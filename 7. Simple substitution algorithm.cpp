#include <stdio.h>
#include <string.h>
char decode(char c) {
    if (c >= 'A' && c <= 'Z') {
        c = 'A' + (c - 'A' + 13) % 26;
    } else if (c >= 'a' && c <= 'z') {
        c = 'a' + (c - 'a' + 13) % 26;
    }
    return c;
}
int main() {
    char ciphertext[1000];
    printf("Enter ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    char plaintext[strlen(ciphertext)];
    for (int i = 0; i < strlen(ciphertext); i++) {
        plaintext[i] = decode(ciphertext[i]);
    }
    printf("Plaintext: %s\n", plaintext);
    return 0;
}

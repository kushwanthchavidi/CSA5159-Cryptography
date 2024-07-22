#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char text[100], key[100];
    int i, j = 0;

    printf("Enter the plaintext: ");
    scanf("%99s",text);
    
    printf("Enter the key: ");
    scanf("%99s",key);

    int text_len = strlen(text);
    int key_len = strlen(key);
    for (i = 0; i < key_len; i++) {
        key[i] = toupper(key[i]);
    }

    printf("Encrypted text: ");
    for (i = 0; i < text_len; i++) {
        char ch = text[i];
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            int shift = toupper(key[j % key_len]) - 'A'; 
            ch = (ch - base + shift) % 26 + base;
            j++; 
        }
        putchar(ch);
    }
    printf("\n");

    return 0;
}

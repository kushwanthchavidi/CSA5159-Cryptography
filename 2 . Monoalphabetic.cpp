#include <stdio.h>
#include <string.h>
char plaintext_alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char ciphertext_alphabet[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
int main() {
    char text[100];
    char encrypted_text[100];
    int i, j;
    printf("Enter a string: ");
    scanf("%99s",text);
    for (i = 0; i < strlen(text); i++) {
        char ch = text[i];
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            int is_upper = (ch >= 'A' && ch <= 'Z');
            ch = is_upper ? ch : ch - 'a' + 'A'; 
            for (j = 0; j < 26; j++) {
                if (plaintext_alphabet[j] == ch) {
                    ch = ciphertext_alphabet[j];
                    break;
                }
            }
            if (!is_upper) {
                ch = ch - 'A' + 'a';
            }
        }
        
        encrypted_text[i] = ch;
    }
    encrypted_text[i] = '\0'; 
    
    printf("Encrypted text: %s\n", encrypted_text);
    
    return 0;
}

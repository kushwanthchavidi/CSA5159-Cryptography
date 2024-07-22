#include <stdio.h>
#include <string.h>
int main() {
    char text[100];
    int k;
    printf("Enter a string: ");
    scanf("%99s",text);
    printf("Enter the shift value (1-25): ");
    scanf("%d", &k);
    if (k < 1 || k > 25) {
        printf("Invalid shift value. Please enter a value between 1 and 25.\n");
        return 1;
    }
    int length = strlen(text);
    for (int i = 0; i < length; i++) {
        char ch = text[i];
        if (ch >= 'A' && ch <= 'Z') {
            ch = (ch - 'A' + k) % 26 + 'A';
        }
        else if (ch >= 'a' && ch <= 'z') {
            ch = (ch - 'a' + k) % 26 + 'a';
        }
        text[i] = ch;
    }
    printf("Encrypted text: %s\n", text);
    return 0;
}

#include <stdio.h>
#include <string.h>
void decrypt(char *ciphertext) {
  char plaintext[strlen(ciphertext)];
  int i;
  for (i = 0; i < strlen(ciphertext); i++) {
    if (ciphertext[i] == 'K') {
      plaintext[i] = 'P';
    } else if (ciphertext[i] == 'X') {
      plaintext[i] = 'T';
    } else if (ciphertext[i] == 'J') {
      plaintext[i] = 'E';
    } else if (ciphertext[i] == 'E') {
      plaintext[i] = 'H';
    } else if (ciphertext[i] == 'Y') {
      plaintext[i] = 'L';
    } else if (ciphertext[i] == 'U') {
      plaintext[i] = 'F';
    } else if (ciphertext[i] == 'R') {
      plaintext[i] = 'O';
    } else if (ciphertext[i] == 'B') {
      plaintext[i] = 'A';
    } else if (ciphertext[i] == 'Z') {
      plaintext[i] = 'M';
    } else if (ciphertext[i] == 'W') {
      plaintext[i] = 'S';
    } else if (ciphertext[i] == 'V') {
      plaintext[i] = 'D';
    } else {
      plaintext[i] = ciphertext[i];
    }
  }

  plaintext[i] = '\0';

  printf("Decrypted text: %s\n", plaintext);
}

int main() {
  char ciphertext[] = "KXJEY UREBE ZWEHE WRYTU HEYFS KREHE GOYFI WTTTU OLKSY CAJPO BOTEI ZONTX BYBNT GONEY CUZWR GDSON SXBOU YWRHE BAAHY USEDQ";

  decrypt(ciphertext);

  return 0;
}

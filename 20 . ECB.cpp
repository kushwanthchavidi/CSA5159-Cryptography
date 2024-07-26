#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#define DES_KEY_SIZE 8
#define DES_BLOCK_SIZE 8
void des_encrypt_block(uint8_t *input, uint8_t *output, uint8_t *key);
void des_decrypt_block(uint8_t *input, uint8_t *output, uint8_t *key);
void print_hex(const char *label, const uint8_t *data, size_t size);
void ecb_encrypt(uint8_t *plaintext, size_t plaintext_len, uint8_t *key, uint8_t *ciphertext);
void ecb_decrypt(uint8_t *ciphertext, size_t ciphertext_len, uint8_t *key, uint8_t *plaintext);
int main() {
    uint8_t key[DES_KEY_SIZE] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1};
    uint8_t plaintext[] = "This is a secret message!";
    size_t plaintext_len = strlen((char *)plaintext);
    uint8_t ciphertext[plaintext_len + DES_BLOCK_SIZE];
    uint8_t decryptedtext[plaintext_len + DES_BLOCK_SIZE];
    ecb_encrypt(plaintext, plaintext_len, key, ciphertext);
    ecb_decrypt(ciphertext, plaintext_len + (DES_BLOCK_SIZE - plaintext_len % DES_BLOCK_SIZE), key, decryptedtext);
    print_hex("Key", key, DES_KEY_SIZE);
    print_hex("Plaintext", plaintext, plaintext_len);
    print_hex("Ciphertext", ciphertext, plaintext_len + (DES_BLOCK_SIZE - plaintext_len % DES_BLOCK_SIZE));
    print_hex("Decrypted Text", decryptedtext, plaintext_len);
    return 0;
}
void print_hex(const char *label, const uint8_t *data, size_t size) {
    printf("%s: ", label);
    for (size_t i = 0; i < size; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}
void des_encrypt_block(uint8_t *input, uint8_t *output, uint8_t *key) {
    memcpy(output, input, DES_BLOCK_SIZE);
}
void des_decrypt_block(uint8_t *input, uint8_t *output, uint8_t *key) {
    memcpy(output, input, DES_BLOCK_SIZE);
}
void ecb_encrypt(uint8_t *plaintext, size_t plaintext_len, uint8_t *key, uint8_t *ciphertext) {
    for (size_t i = 0; i < plaintext_len; i += DES_BLOCK_SIZE) {
        uint8_t block[DES_BLOCK_SIZE] = {0};
        size_t block_len = (plaintext_len - i) >= DES_BLOCK_SIZE ? DES_BLOCK_SIZE : (plaintext_len - i);
        memcpy(block, plaintext + i, block_len);
        des_encrypt_block(block, ciphertext + i, key);
    }
}
void ecb_decrypt(uint8_t *ciphertext, size_t ciphertext_len, uint8_t *key, uint8_t *plaintext) {
    for (size_t i = 0; i < ciphertext_len; i += DES_BLOCK_SIZE) {
        uint8_t block[DES_BLOCK_SIZE] = {0};
        size_t block_len = (ciphertext_len - i) >= DES_BLOCK_SIZE ? DES_BLOCK_SIZE : (ciphertext_len - i);
        memcpy(block, ciphertext + i, block_len);
        des_decrypt_block(block, plaintext + i, key);
    }
}
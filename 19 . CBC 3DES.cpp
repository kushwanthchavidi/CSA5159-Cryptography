#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define DES_KEY_SIZE 8
#define DES_BLOCK_SIZE 8
#define DES3_KEY_SIZE (3 * DES_KEY_SIZE)

// S-box and permutation tables would go here (omitted for brevity)

// Placeholder DES encryption function (implement DES encryption here)
void des_encrypt_block(uint8_t *input, uint8_t *output, uint8_t *key);

// Placeholder DES decryption function (implement DES decryption here)
void des_decrypt_block(uint8_t *input, uint8_t *output, uint8_t *key);

void xor_blocks(uint8_t *dst, const uint8_t *src1, const uint8_t *src2, size_t size);
void generate_random_bytes(uint8_t *buffer, size_t size);
void print_hex(const char *label, const uint8_t *data, size_t size);

void triple_des_encrypt_cbc(uint8_t *plaintext, size_t plaintext_len, uint8_t *key, uint8_t *iv, uint8_t *ciphertext);
void triple_des_decrypt_cbc(uint8_t *ciphertext, size_t ciphertext_len, uint8_t *key, uint8_t *iv, uint8_t *plaintext);

int main() {
    uint8_t key[DES3_KEY_SIZE];
    uint8_t iv[DES_BLOCK_SIZE];
    uint8_t plaintext[] = "This is a secret message!";
    size_t plaintext_len = strlen((char *)plaintext);
    uint8_t ciphertext[plaintext_len + DES_BLOCK_SIZE];
    uint8_t decryptedtext[plaintext_len + DES_BLOCK_SIZE];

    // Generate random key and IV
    generate_random_bytes(key, DES3_KEY_SIZE);
    generate_random_bytes(iv, DES_BLOCK_SIZE);

    // Encrypt the plaintext
    triple_des_encrypt_cbc(plaintext, plaintext_len, key, iv, ciphertext);

    // Decrypt the ciphertext
    triple_des_decrypt_cbc(ciphertext, plaintext_len + (DES_BLOCK_SIZE - plaintext_len % DES_BLOCK_SIZE), key, iv, decryptedtext);

    // Print key, IV, ciphertext, and decrypted text
    print_hex("Key", key, DES3_KEY_SIZE);
    print_hex("IV", iv, DES_BLOCK_SIZE);
    print_hex("Ciphertext", ciphertext, plaintext_len + (DES_BLOCK_SIZE - plaintext_len % DES_BLOCK_SIZE));
    print_hex("Decrypted Text", decryptedtext, plaintext_len);

    return 0;
}

void generate_random_bytes(uint8_t *buffer, size_t size) {
    FILE *urandom = fopen("/dev/urandom", "r");
    if (!urandom) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fread(buffer, 1, size, urandom);
    fclose(urandom);
}

void print_hex(const char *label, const uint8_t *data, size_t size) {
    printf("%s: ", label);
    for (size_t i = 0; i < size; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

void xor_blocks(uint8_t *dst, const uint8_t *src1, const uint8_t *src2, size_t size) {
    for (size_t i = 0; i < size; i++) {
        dst[i] = src1[i] ^ src2[i];
    }
}

void des_encrypt_block(uint8_t *input, uint8_t *output, uint8_t *key) {
    // Implement DES encryption for a single block here
    // This is a placeholder function
    memcpy(output, input, DES_BLOCK_SIZE);
}

void des_decrypt_block(uint8_t *input, uint8_t *output, uint8_t *key) {
    // Implement DES decryption for a single block here
    // This is a placeholder function
    memcpy(output, input, DES_BLOCK_SIZE);
}

void triple_des_encrypt_cbc(uint8_t *plaintext, size_t plaintext_len, uint8_t *key, uint8_t *iv, uint8_t *ciphertext) {
    uint8_t iv_copy[DES_BLOCK_SIZE];
    memcpy(iv_copy, iv, DES_BLOCK_SIZE);

    for (size_t i = 0; i < plaintext_len; i += DES_BLOCK_SIZE) {
        uint8_t block[DES_BLOCK_SIZE] = {0};
        size_t block_len = (plaintext_len - i) >= DES_BLOCK_SIZE ? DES_BLOCK_SIZE : (plaintext_len - i);

        memcpy(block, plaintext + i, block_len);
        xor_blocks(block, block, iv_copy, DES_BLOCK_SIZE);

        uint8_t temp[DES_BLOCK_SIZE];
        des_encrypt_block(block, temp, key);
        des_decrypt_block(temp, block, key + DES_KEY_SIZE);
        des_encrypt_block(block, temp, key + 2 * DES_KEY_SIZE);

        memcpy(ciphertext + i, temp, DES_BLOCK_SIZE);
        memcpy(iv_copy, temp, DES_BLOCK_SIZE);
    }
}

void triple_des_decrypt_cbc(uint8_t *ciphertext, size_t ciphertext_len, uint8_t *key, uint8_t *iv, uint8_t *plaintext) {
    uint8_t iv_copy[DES_BLOCK_SIZE];
    memcpy(iv_copy, iv, DES_BLOCK_SIZE);

    for (size_t i = 0; i < ciphertext_len; i += DES_BLOCK_SIZE) {
        uint8_t temp[DES_BLOCK_SIZE];
        uint8_t block[DES_BLOCK_SIZE];

        memcpy(temp, ciphertext + i, DES_BLOCK_SIZE);
        des_decrypt_block(temp, block, key + 2 * DES_KEY_SIZE);
        des_encrypt_block(block, temp, key + DES_KEY_SIZE);
        des_decrypt_block(temp, block, key);

        xor_blocks(block, block, iv_copy, DES_BLOCK_SIZE);

        memcpy(plaintext + i, block, DES_BLOCK_SIZE);
        memcpy(iv_copy, ciphertext + i, DES_BLOCK_SIZE);
    }
}

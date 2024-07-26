#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define DES_KEY_SIZE 8
#define DES_BLOCK_SIZE 8
static const int PC1_left[28] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 
    18, 10, 2, 59, 51, 43, 
    35, 27, 19, 11, 3, 60, 
    52, 44
};
static const int PC1_right[28] = {
    63, 55, 47, 39, 31, 23, 15, 
    7, 62, 54, 46, 38, 30, 22, 
    14, 6, 61, 53, 45, 37, 
    29, 21, 13, 5, 28, 20, 
    12, 4
};
static const int PC2[48] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};
static const int shift_schedule[16] = {
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1
};
void generate_keys(uint8_t key[DES_KEY_SIZE], uint8_t round_keys[16][6]);
void print_subkey(uint8_t subkey[6]);
int main() {
    uint8_t key[DES_KEY_SIZE] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1};
    uint8_t round_keys[16][6];
    generate_keys(key, round_keys);
    for (int i = 0; i < 16; i++) {
        printf("Round %2d key: ", i + 1);
        print_subkey(round_keys[i]);
    }
    return 0;
}
void generate_keys(uint8_t key[DES_KEY_SIZE], uint8_t round_keys[16][6]) {
    uint8_t C[4] = {0}; 
    uint8_t D[4] = {0}; 
    uint64_t combined_key = 0;
    for (int i = 0; i < 28; i++) {
        int byte_index = (PC1_left[i] - 1) / 8;
        int bit_index = (PC1_left[i] - 1) % 8;
        int bit = (key[byte_index] >> (7 - bit_index)) & 1;
        C[i / 8] |= bit << (7 - (i % 8));
    }
    for (int i = 0; i < 28; i++) {
        int byte_index = (PC1_right[i] - 1) / 8;
        int bit_index = (PC1_right[i] - 1) % 8;
        int bit = (key[byte_index] >> (7 - bit_index)) & 1;
        D[i / 8] |= bit << (7 - (i % 8));
    }
    for (int round = 0; round < 16; round++) {
        int shifts = shift_schedule[round];
        uint32_t C_int = ((uint32_t)C[0] << 24) | ((uint32_t)C[1] << 16) | ((uint32_t)C[2] << 8) | (uint32_t)C[3];
        uint32_t D_int = ((uint32_t)D[0] << 24) | ((uint32_t)D[1] << 16) | ((uint32_t)D[2] << 8) | (uint32_t)D[3];
        C_int = ((C_int << shifts) | (C_int >> (28 - shifts))) & 0x0FFFFFFF;
        D_int = ((D_int << shifts) | (D_int >> (28 - shifts))) & 0x0FFFFFFF;
        C[0] = (C_int >> 24) & 0xFF;
        C[1] = (C_int >> 16) & 0xFF;
        C[2] = (C_int >> 8) & 0xFF;
        C[3] = C_int & 0xFF;
        D[0] = (D_int >> 24) & 0xFF;
        D[1] = (D_int >> 16) & 0xFF;
        D[2] = (D_int >> 8) & 0xFF;
        D[3] = D_int & 0xFF;
        combined_key = ((uint64_t)C_int << 28) | (uint64_t)D_int;
        for (int i = 0; i < 48; i++) {
            int bit = (combined_key >> (56 - PC2[i])) & 1;
            round_keys[round][i / 8] |= bit << (7 - (i % 8));
        }
    }
}
void print_subkey(uint8_t subkey[6]) {
    for (int i = 0; i < 6; i++) {
        printf("%02X ", subkey[i]);
    }
    printf("\n");
}

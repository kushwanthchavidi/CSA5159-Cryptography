#include <stdio.h>
#include <stdint.h>
#include <cstring>
#define DES_KEY_SIZE 8
#define DES_BLOCK_SIZE 8
static const int IP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};
static const int FP[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};
static const int E[48] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};
static const int S[8][4][16] = {

    {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
     {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
     {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
     {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},

    {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
     {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
     {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
     {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},

    {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
     {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
     {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
     {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},

    {{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
     {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
     {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
     {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},

    {{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
     {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
     {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
     {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},

    {{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
     {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
     {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
     {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},

    {{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
     {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
     {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
     {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},

    {{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
     {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
     {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
     {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}
};
static const int P[32] = {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25
};
static const int PC1[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
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
void initial_permutation(uint8_t *block);
void final_permutation(uint8_t *block);
void des_round(uint32_t *L, uint32_t *R, uint8_t *round_key);
uint32_t f(uint32_t R, uint8_t *round_key);
void des_decrypt(uint8_t *ciphertext, uint8_t *plaintext, uint8_t round_keys[16][6]);
int main() {
    uint8_t key[DES_KEY_SIZE] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1};
    uint8_t ciphertext[DES_BLOCK_SIZE] = {0x85, 0xE8, 0x13, 0x54, 0x0F, 0x0A, 0xB4, 0x05};
    uint8_t plaintext[DES_BLOCK_SIZE];
    uint8_t round_keys[16][6];
    generate_keys(key, round_keys);
    des_decrypt(ciphertext, plaintext, round_keys);
    for (int i = 0; i < DES_BLOCK_SIZE; i++) {
        printf("%02x ", plaintext[i]);
    }
    printf("\n");
    return 0;
}
void generate_keys(uint8_t key[DES_KEY_SIZE], uint8_t round_keys[16][6]) {
    uint8_t permuted_key[7] = {0};
    for (int i = 0; i < 56; i++) {
        int byte_index = (PC1[i] - 1) / 8;
        int bit_index = (PC1[i] - 1) % 8;
        int bit = (key[byte_index] >> (7 - bit_index)) & 1;
        permuted_key[i / 8] |= bit << (7 - (i % 8));
    }
    uint32_t C = ((uint32_t)permuted_key[0] << 24) | ((uint32_t)permuted_key[1] << 16) | ((uint32_t)permuted_key[2] << 8) | (uint32_t)permuted_key[3];
    uint32_t D = ((uint32_t)permuted_key[4] << 24) | ((uint32_t)permuted_key[5] << 16) | ((uint32_t)permuted_key[6] << 8);
    for (int round = 0; round < 16; round++) {
        int shifts = shift_schedule[round];
        C = ((C << shifts) | (C >> (28 - shifts))) & 0x0FFFFFFF;
        D = ((D << shifts) | (D >> (28 - shifts))) & 0x0FFFFFFF;

        uint64_t combined_key = ((uint64_t)C << 28) | (uint64_t)D;
        for (int i = 0; i < 48; i++) {
            int bit = (combined_key >> (56 - PC2[i])) & 1;
            round_keys[round][i / 8] |= bit << (7 - (i % 8));
        }
    }
}
void initial_permutation(uint8_t *block) {
    uint8_t temp[DES_BLOCK_SIZE] = {0};
    for (int i = 0; i < 64; i++) {
        int byte_index = (IP[i] - 1) / 8;
        int bit_index = (IP[i] - 1) % 8;
        int bit = (block[byte_index] >> (7 - bit_index)) & 1;
        temp[i / 8] |= bit << (7 - (i % 8));
    }
    memcpy(block, temp, DES_BLOCK_SIZE);
}
void final_permutation(uint8_t *block) {
    uint8_t temp[DES_BLOCK_SIZE] = {0};
    for (int i = 0; i < 64; i++) {
        int byte_index = (FP[i] - 1) / 8;
        int bit_index = (FP[i] - 1) % 8;
        int bit = (block[byte_index] >> (7 - bit_index)) & 1;
        temp[i / 8] |= bit << (7 - (i % 8));
    }
    memcpy(block, temp, DES_BLOCK_SIZE);
}
uint32_t f(uint32_t R, uint8_t *round_key) {
    uint64_t expanded_R = 0;
    for (int i = 0; i < 48; i++) {
        int bit = (R >> (32 - E[i])) & 1;
        expanded_R |= (uint64_t)bit << (47 - i);
    }
    expanded_R ^= *((uint64_t *)round_key);
    uint32_t output = 0;
    for (int i = 0; i < 8; i++) {
        int row = ((expanded_R >> (42 - 6 * i)) & 0x20) | ((expanded_R >> (42 - 6 * i - 5)) & 0x01);
        int col = (expanded_R >> (42 - 6 * i - 1)) & 0x0F;
        output |= S[i][row][col] << (28 - 4 * i);
    }
    uint32_t permuted_output = 0;
    for (int i = 0; i < 32; i++) {
        int bit = (output >> (32 - P[i])) & 1;
        permuted_output |= bit << (31 - i);
    }
    return permuted_output;
}
void des_round(uint32_t *L, uint32_t *R, uint8_t *round_key) {
    uint32_t temp = *R;
    *R = *L ^ f(*R, round_key);
    *L = temp;
}
void des_decrypt(uint8_t *ciphertext, uint8_t *plaintext, uint8_t round_keys[16][6]) {
    initial_permutation(ciphertext);
    uint32_t L = ((uint32_t)ciphertext[0] << 24) | ((uint32_t)ciphertext[1] << 16) | ((uint32_t)ciphertext[2] << 8) | (uint32_t)ciphertext[3];
    uint32_t R = ((uint32_t)ciphertext[4] << 24) | ((uint32_t)ciphertext[5] << 16) | ((uint32_t)ciphertext[6] << 8) | (uint32_t)ciphertext[7];
    for (int i = 15; i >= 0; i--) {
        des_round(&L, &R, round_keys[i]);
    }
    uint32_t combined = (R << 32) | L;
    for (int i = 0; i < 8; i++) {
        plaintext[i] = (combined >> (56 - 8 * i)) & 0xFF;
    }
    final_permutation(plaintext);
}

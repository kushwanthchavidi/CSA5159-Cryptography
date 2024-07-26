#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 3 
#define MOD 26
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 0) return x;
    }
    return -1;
}
int determinant(int matrix[N][N], int n) {
    int det = 0;
    int submatrix[N][N];
    if (n == 1) return matrix[0][0];
    if (n == 2) return (matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1]);
    for (int x = 0; x < n; x++) {
        int subi = 0;
        for (int i = 1; i < n; i++) {
            int subj = 0;
            for (int j = 0; j < n; j++) {
                if (j == x) continue;
                submatrix[subi][subj] = matrix[i][j];
                subj++;
            }
            subi++;
        }
        det = det + (x % 2 == 0 ? 1 : -1) * matrix[0][x] * determinant(submatrix, n - 1);
    }
    return det;
}
void adjoint(int A[N][N], int adj[N][N]) {
    if (N == 1) {
        adj[0][0] = 1;
        return;
    }
    int sign = 1, temp[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int subi = 0;
            for (int x = 0; x < N; x++) {
                if (x == i) continue;
                int subj = 0;
                for (int y = 0; y < N; y++) {
                    if (y == j) continue;
                    temp[subi][subj] = A[x][y];
                    subj++;
                }
                subi++;
            }
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = (sign) * (determinant(temp, N - 1));
        }
    }
}
int inverse(int A[N][N], int inverse[N][N]) {
    int det = determinant(A, N);
    int invDet = modInverse(det, MOD);
    if (invDet == -1) {
        printf("Inverse doesn't exist");
        return 0;
    }
    int adj[N][N];
    adjoint(A, adj);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            inverse[i][j] = (adj[i][j] * invDet) % MOD;
    return 1;
}
void multiply(int mat1[N][N], int mat2[N][N], int res[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            res[i][j] = 0;
            for (int k = 0; k < N; k++)
                res[i][j] += mat1[i][k] * mat2[k][j];
            res[i][j] = res[i][j] % MOD;
        }
    }
}
void printMatrix(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
int main() {
    int plaintext[N][N] = {
        {7, 4, 11},  
        {4, 11, 11}, 
        {11, 14, 22} 
    };
    int ciphertext[N][N] = {
        {13, 5, 21}, 
        {14, 12, 6},
        {6, 14, 14}
    };
    int invPlaintext[N][N];
    if (inverse(plaintext, invPlaintext)) {
        printf("Inverse of the plaintext matrix:\n");
        printMatrix(invPlaintext);
        int key[N][N];
        multiply(invPlaintext, ciphertext, key);
        printf("Key matrix:\n");
        printMatrix(key);
    } else {
        printf("Could not compute inverse of the plaintext matrix.\n");
    }
    return 0;
}
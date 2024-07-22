#include <stdio.h>
#include <math.h>

int main() {
    // Constants
    double factorial_25 = 1.55e25;
    double log2_25_factorial = log2(factorial_25);
    double log2_10 = log2(10);
    double approx_log2_25_factorial = log2_25_factorial + 25 * log2_10;

    // Part 1: Possible keys
    double possible_keys_log2 = approx_log2_25_factorial;
    printf("Possible keys (ignoring identical results): 2^%.2f\n", possible_keys_log2);

    // Part 2: Effectively unique keys
    double unique_keys_log2 = possible_keys_log2 - 3; // log2(8) = 3
    printf("Effectively unique keys: 2^%.2f\n", unique_keys_log2);

    return 0;
}

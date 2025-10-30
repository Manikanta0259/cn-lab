#include <stdio.h>
#include <math.h>

int main() {
    int data[10], ham[10];
    int i, j, k, r = 0, n;

    printf("Enter number of data bits: ");
    scanf("%d", &n);

    printf("Enter data bits (from MSB to LSB): ");
    for(i = n; i >= 1; i--)
        scanf("%d", &data[i]);

    // Find number of parity bits needed
    for(r = 1; pow(2, r) < n + r + 1; r++);

    printf("Number of parity bits: %d\n", r);

    // Insert parity bits into positions 1, 2, 4, 8, ...
    j = k = 0;
    for(i = 1; i <= n + r; i++) {
        if(pow(2, j) == i) {
            ham[i] = 0; // Placeholder for parity bit
            j++;
        } else {
            ham[i] = data[++k];
        }
    }

    // Calculate parity bits
    for(i = 0; i < r; i++) {
        int pos = pow(2, i);
        int parity = 0;
        for(j = pos; j <= n + r; j++) {
            if(((j >> i) & 1) == 1)
                parity ^= ham[j];
        }
        ham[pos] = parity;
    }

    // Display final Hamming code
    printf("Generated Hamming code: ");
    for(i = n + r; i >= 1; i--)
        printf("%d ", ham[i]);

    printf("\n");
    return 0;
}

#include <stdio.h>
#include <string.h>

int binaryToDecimal(const char *binary) {
    int decimal = 0;
    for (int i = 0; binary[i] != '\0'; i++) {
        decimal = decimal * 2 + (binary[i] - '0');
    }
    return decimal;
}

void decimalToBinary(int decimal, char *binary, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        binary[i] = (decimal & 1) + '0';
        decimal >>= 1;
    }
    binary[bits] = '\0';
}

int main() {
    char bin1[50], bin2[50], checksumBinary[50];
    int num1, num2, sum, checksum, bits;

    printf("Enter no. of bits: ");
    scanf("%d", &bits);

    printf("Enter binary number (1st, %d bits): ", bits);
    scanf("%s", bin1);

    printf("Enter second binary number (%d bits): ", bits);
    scanf("%s", bin2);

    num1 = binaryToDecimal(bin1);
    num2 = binaryToDecimal(bin2);

    sum = num1 + num2;

    if (sum >= (1 << bits)) {
        sum = (sum % (1 << bits)) + 1;
    }

    checksum = ((1 << bits) - 1) - sum;

    decimalToBinary(checksum, checksumBinary, bits);
    printf("Calculated checksum is: %s\n", checksumBinary);

    int verify_sum = num1 + num2 + checksum;

    if (verify_sum >= (1 << bits)) {
        verify_sum = (verify_sum % (1 << bits)) + 1;
    }

    if (verify_sum == ((1 << bits) - 1)) {
        printf("Data received successfully (No error)\n");
    } else {
        printf("Data corrupted (Error detected)\n");
    }

    return 0;
}
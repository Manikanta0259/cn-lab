//Write a Program to implement on a data set of characters the three CRC polynomials – CRC 12, CRC 16 and CRC CCIP.
#include <stdio.h>
#include <string.h>

unsigned short crc12(const char *data) {
    unsigned short crc = 0;
    unsigned short poly = 0x80F;
    for (int i = 0; data[i]; i++) {
        crc ^= (data[i] << 4);
        for (int j = 0; j < 8; j++)
            crc = (crc & 0x800) ? ((crc << 1) ^ poly) : (crc << 1);
    }
    return crc & 0xFFF;
}

unsigned short crc16(const char *data) {
    unsigned short crc = 0xFFFF;
    unsigned short poly = 0x8005;
    for (int i = 0; data[i]; i++) {
        crc ^= (data[i] << 8);
        for (int j = 0; j < 8; j++)
            crc = (crc & 0x8000) ? ((crc << 1) ^ poly) : (crc << 1);
    }
    return crc;
}

unsigned short crc_ccitt(const char *data) {
    unsigned short crc = 0xFFFF;
    unsigned short poly = 0x1021;
    for (int i = 0; data[i]; i++) {
        crc ^= (data[i] << 8);
        for (int j = 0; j < 8; j++)
            crc = (crc & 0x8000) ? ((crc << 1) ^ poly) : (crc << 1);
    }
    return crc;
}

int main() {
    char data[100];
    printf("Enter data: ");
    scanf("%s", data);
    printf("CRC-12: %03X\n", crc12(data));
    printf("CRC-16: %04X\n", crc16(data));
    printf("CRC-CCITT: %04X\n", crc_ccitt(data));
    return 0;
}
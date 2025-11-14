// 6. Write a Program to implement Sliding window protocol for Goback N. 
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, window, i, j, ack, frames[50];
    printf("Enter number of frames: ");
    scanf("%d", &n);
    printf("Enter window size: ");
    scanf("%d", &window);
    printf("Enter %d frames: ", n);
    for (i = 0; i < n; i++) scanf("%d", &frames[i]);
    i = 0;
    while (i < n) {
        for (j = i; j < i + window && j < n; j++)
            printf("Frame %d sent\n", frames[j]);
        for (j = i; j < i + window && j < n; j++) {
            printf("Acknowledge for frame %d (1=success,0=lost): ", frames[j]);
            scanf("%d", &ack);
            if (ack == 0) break;
        }
        if (ack == 0) {
            printf("Timeout! Resending from frame %d\n", frames[j]);
            i = j;
        } else i = i + window;
    }
    printf("All frames transmitted successfully.\n");
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int frames;
    printf("Enter the number of frames to send: ");
    scanf("%d", &frames);

    srand(time(0));  // Seed for random number generation

    printf("\n--- Stop and Wait Protocol Simulation ---\n");

    for (int i = 1; i <= frames; i++) {
        printf("\nSending Frame %d...", i);
        int ack = rand() % 2;  // Randomly decide if ACK is received (0 = lost, 1 = received)

        if (ack == 1) {
            printf("\nAcknowledgment for Frame %d received.", i);
        } else {
            printf("\nAcknowledgment for Frame %d lost. Retransmitting...", i);
            printf("\nResending Frame %d...", i);
            printf("\nAcknowledgment for Frame %d received.", i);
        }
    }

    printf("\n\nAll frames sent successfully!\n");
    return 0;
}

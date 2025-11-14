#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FRAMES 50

int main() {
    int total_frames, window_size;
    int frame_sent = 0; // Index of the current frame being sent

    printf("Enter the total number of frames to send: ");
    scanf("%d", &total_frames);

    printf("Enter the window size: ");
    scanf("%d", &window_size);

    srand(time(0)); // Seed for random number generator

    printf("\n--- Selective Repeat ARQ Simulation ---\n");

    while (frame_sent < total_frames) {
        printf("\n\nSending frames: ");
        // Send frames within the window
        for (int i = frame_sent; i < frame_sent + window_size && i < total_frames; i++) {
            printf("Frame %d ", i);
        }

        printf("\n");

        // Simulate acknowledgment or loss for each frame
        for (int i = frame_sent; i < frame_sent + window_size && i < total_frames; i++) {
            int ack = rand() % 2;  // Randomly generate ACK (1 = received, 0 = lost)

            if (ack == 1) {
                printf("ACK received for Frame %d\n", i);
            } else {
                printf("ACK lost for Frame %d. Retransmitting...\n", i);
                printf("Resending Frame %d\n", i);
                printf("ACK received for Frame %d\n", i);
            }
        }

        frame_sent += window_size; // Move the window forward
    }

    printf("\nAll frames sent successfully!\n");

    return 0;
}

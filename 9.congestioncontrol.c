//. Write a program for congestion control using leaky bucket algorithm 
#include <stdio.h>

int main() {
    int bucket_size, output_rate, n, incoming, stored = 0, sent;
    printf("Enter bucket size: ");
    scanf("%d", &bucket_size);
    printf("Enter output rate: ");
    scanf("%d", &output_rate);
    printf("Enter number of packets: ");
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        printf("Enter incoming packet size at time %d: ", i);
        scanf("%d", &incoming);
        if (incoming + stored > bucket_size) {
            printf("Bucket overflow! %d packets discarded.\n", (incoming + stored) - bucket_size);
            stored = bucket_size;
        } else stored += incoming;
        sent = (stored >= output_rate) ? output_rate : stored;
        stored -= sent;
        printf("Sent: %d\tRemaining in bucket: %d\n", sent, stored);
    }
    while (stored > 0) {
        sent = (stored >= output_rate) ? output_rate : stored;
        stored -= sent;
        printf("Sent: %d\tRemaining in bucket: %d\n", sent, stored);
    }
    return 0;
}
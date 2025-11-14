#include <stdio.h>

#define INFINITY 999
#define MAX 10

void distanceVectorRouting(int cost[MAX][MAX], int n) {
    int dist[MAX][MAX], nextHop[MAX][MAX];
    int i, j, k, updated;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            dist[i][j] = cost[i][j];
            if (i == j || cost[i][j] == INFINITY)
                nextHop[i][j] = -1;
            else
                nextHop[i][j] = j;
        }
    }

    do {
        updated = 0;

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                for (k = 0; k < n; k++) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        nextHop[i][j] = nextHop[i][k];
                        updated = 1;
                    }
                }
            }
        }

    } while (updated);

    for (i = 0; i < n; i++) {
        printf("\nRouting table for node %d\n", i);
        printf("Destination   NextHop   Distance\n");

        for (j = 0; j < n; j++) {
            if (i == j) continue;
            printf("%d\t\t%d\t\t%d\n", j, nextHop[i][j], dist[i][j]);
        }
    }
}

int main() {
    int n, i, j;
    int cost[MAX][MAX];

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter cost matrix (use 999 for infinity):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    distanceVectorRouting(cost, n);

    return 0;
}
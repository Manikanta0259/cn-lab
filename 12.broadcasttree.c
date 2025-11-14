//12. Write a Program to implement Broadcast tree by taking subnet of hosts.
#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int parent[MAX];

// Find operation for union-find
int find(int i) {
    while (parent[i])
        i = parent[i];
    return i;
}

// Union operation for union-find
int uni(int i, int j) {
    if (i != j) {
        parent[j] = i;
        return 1;
    }
    return 0;
}

int main() {
    int n, i, j, u, v, a, b, min, ne = 1;
    int cost[MAX][MAX], mincost = 0;

    printf("Enter the number of nodes:");
    scanf("%d", &n);

    printf("Enter the adjacency matrix (use 999 for no direct connection):");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    printf("Broadcast tree edges:");
    while (ne < n) {
        for (i = 1, min = 999; i <= n; i++) {
            for (j = 1; j <= n; j++) {
                if (cost[i][j] < min && i != j) {
                    min = cost[i][j];
                    a = u = i;
                    b = v = j;
                }
            }
        }
        u = find(u);
        v = find(v);

        if (uni(u, v)) {
            printf("%d -> %d (Cost: %d)", a, b, min);
            mincost += min;
        }
        cost[a][b] = cost[b][a] = 999; // Remove the edge
        ne++;
    }
    printf("Minimum cost = %d", mincost);
    return 0;
} 
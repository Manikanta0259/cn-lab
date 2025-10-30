#include <stdio.h>
#include <limits.h>

#define MAX 10  // Maximum number of vertices

// Function to find the vertex with minimum distance value
int minDistance(int dist[], int visited[], int n) {
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < n; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to print the shortest distances
void printSolution(int dist[], int n, int src) {
    printf("\nShortest distances from source vertex %d:\n", src);
    printf("Vertex\tDistance\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\n", i, dist[i]);
    }
}

// Function that implements Dijkstra’s algorithm
void dijkstra(int graph[MAX][MAX], int n, int src) {
    int dist[MAX];     // dist[i] will hold the shortest distance from src to i
    int visited[MAX];  // visited[i] is true if vertex i is included in shortest path tree

    // Step 1: Initialize all distances as INFINITE and visited[] as false
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Step 2: Find the shortest path for all vertices
    for (int count = 0; count < n - 1; count++) {
        int u = minDistance(dist, visited, n);
        visited[u] = 1; // Mark the picked vertex as processed

        // Step 3: Update dist[v]
        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printSolution(dist, n, src);
}

// Main Function
int main() {
    int n, src;
    int graph[MAX][MAX];

    printf("Enter number of vertices (max %d): ", MAX);
    scanf("%d", &n);

    printf("\nEnter the adjacency matrix (0 if no edge):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("\nEnter the source vertex: ");
    scanf("%d", &src);

    dijkstra(graph, n, src);

    return 0;
}

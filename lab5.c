#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 20
#define MAX_M (MAX_N * (MAX_N - 1))

int adj[MAX_N][MAX_N];
int inc[MAX_N][MAX_M];

void print_adj(int n) {
    printf("Adjacency matrix:\n    ");
    for (int j = 0; j < n; j++) printf("v%-2d ", j + 1);
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("v%-2d ", i + 1);
        for (int j = 0; j < n; j++) printf("%-3d ", adj[i][j]);
        printf("\n");
    }
}

void print_inc(int n, int m) {
    printf("Incidence matrix:\n    ");
    for (int j = 0; j < m; j++) printf("e%-2d ", j + 1);
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("v%-2d ", i + 1);
        for (int j = 0; j < m; j++) printf("%-3d ", inc[i][j]);
        printf("\n");
    }
}

void print_vertices(const char *title, int n, const int deg[], int value) {
    int found = 0;
    printf("%s: ", title);
    for (int i = 0; i < n; i++)
        if (deg[i] == value) { printf("v%d ", i + 1); found = 1; }
    if (!found) printf("none");
    printf("\n");
}

void print_vertex_types(int n, const int deg[], const int dom[]) {
    print_vertices("Isolated vertices", n, deg, 0);
    print_vertices("Pendant vertices", n, deg, 1);
    print_vertices("Dominating vertices", n, dom, n - 1);
}

int main(void) {
    int n, directed, p;

    printf("Choose graph type:\n");
    printf("  1 - Undirected\n");
    printf("  2 - Directed\n");
    printf("Your choice: ");
    if (scanf("%d", &directed) != 1 || (directed != 1 && directed != 2)) {
        printf("Invalid input.\n");
        return 1;
    }
    directed = (directed == 2);

    printf("Enter number of vertices (2..%d): ", MAX_N);
    if (scanf("%d", &n) != 1 || n < 2 || n > MAX_N) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter edge probability in percent (0..100): ");
    if (scanf("%d", &p) != 1 || p < 0 || p > 100) {
        printf("Invalid input.\n");
        return 1;
    }
    srand((unsigned int)time(NULL));

    printf("\n=== Task 1 ===\n");

    if (directed) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (i != j) adj[i][j] = rand() % 100 < p;
    } else {
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                adj[i][j] = adj[j][i] = rand() % 100 < p;
    }
    print_adj(n);

    int deg1[MAX_N] = {0};
    int out1[MAX_N] = {0};
    int sum = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            deg1[i] += adj[i][j];
            sum += adj[i][j];
        }
    for (int i = 0; i < n; i++) {
        out1[i] = deg1[i];
        if (directed)
            for (int j = 0; j < n; j++) deg1[i] += adj[j][i];
    }
    printf("Graph size: %d\n", directed ? sum : sum / 2);
    print_vertex_types(n, deg1, out1);

    printf("\n=== Task 2 ===\n");

    int m = 0;
    if (directed) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (i != j && adj[i][j]) {
                    inc[i][m] = 1;
                    inc[j][m] = -1;
                    m++;
                }
    } else {
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (adj[i][j]) {
                    inc[i][m] = 1;
                    inc[j][m] = 1;
                    m++;
                }
    }
    if (m > 0) print_inc(n, m);

    int deg2[MAX_N] = {0};
    int out2[MAX_N] = {0};
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            deg2[i] += inc[i][j] != 0;
            out2[i] += inc[i][j] == 1;
        }
    if (!directed)
        for (int i = 0; i < n; i++) out2[i] = deg2[i];

    printf("Graph size: %d\n", m);
    print_vertex_types(n, deg2, out2);

    return 0;
}
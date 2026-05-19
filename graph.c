#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

weightedAdjacencyMatrix* createMatrix(int matrixSize) {
    weightedAdjacencyMatrix *matrix = (weightedAdjacencyMatrix*)malloc(sizeof(weightedAdjacencyMatrix));
    if (matrix == NULL) {
        printf("Error: memory allocation failed.\n");
        return NULL;
    }

    matrix->matrixSize = matrixSize;

    matrix->weight = (int**)malloc(matrixSize * sizeof(int*));
    if (matrix->weight == NULL) {
        printf("Error: memory allocation failed.\n");
        return NULL;
    }
    for (int i = 0; i < matrixSize; ++i) {
        matrix->weight[i] = (int*)malloc(matrixSize * sizeof(int));
        if (matrix->weight[i] == NULL) {
        printf("Error: memory allocation failed.\n");
        return NULL;
    }
        for (int j = 0; j < matrixSize; ++j) {
            if (i != j)
                matrix->weight[i][j] = -1;
            else
                matrix->weight[i][j] = 0;
        }
    }

    return matrix;
}

void deleteMatrix(weightedAdjacencyMatrix* matrix) {
    if (matrix == NULL) {
        printf("Error: pointer cannot be NULL.\n");
        return;
    }

    for (int i = 0; i < matrix->matrixSize; ++i) {
        free(matrix->weight[i]);
    }
    free(matrix->weight);

    free(matrix);
}

void visualize(weightedAdjacencyMatrix* matrix) {
    if (matrix == NULL) {
        printf("Error: pointer cannot be NULL.\n");
        return;
    }

    printf("      ");
    for (int j = 0; j < matrix->matrixSize; ++j) {
        printf("%5d", j);
    }
    printf("\n");

    for (int i = 0; i < matrix->matrixSize; ++i) {
        printf("%5d ", i);

        for (int j = 0; j < matrix->matrixSize; ++j)
            printf("%5d", matrix->weight[i][j]);
        printf("\n");
    }
}

int dijkstra(weightedAdjacencyMatrix* matrix, int sourceMember, int destinationMember, int* path) {
    if (matrix == NULL) {
        printf("Error: pointer cannot be NULL.\n");
        return -1;
    }

    int distances[matrix->matrixSize];
    bool visited[matrix->matrixSize];
    for (int i = 0; i < matrix->matrixSize; ++i) {
        if (i != sourceMember)
            distances[i] = -1;
        else
            distances[i] = 0;

        visited[i] = 0;
        path[i] = -1; // Possible error here, if the capacity of path[] array is smaller than the matrixSize
    }

    for (int i = 0; i < matrix->matrixSize; ++i) {
        int minDistance = -1;
        int minIndex = -1;

        for (int j = 0; j < matrix->matrixSize; ++j) {
            if (distances[j] != -1 && !visited[j]) {
                if (minDistance == -1 || distances[j] < minDistance) {
                    minDistance = distances[j];
                    minIndex = j;
                }
            }
        }

        if (minIndex == -1)
            return -1;

        if (minIndex == destinationMember)
            return distances[minIndex];

        visited[minIndex] = 1;
        for (int j = 0; j < matrix->matrixSize; ++j) {
            if (matrix->weight[minIndex][j] != -1 && !visited[j]
                    && (distances[j] > distances[minIndex] + matrix->weight[minIndex][j] || distances[j] == -1)) {
                distances[j] = distances[minIndex] + matrix->weight[minIndex][j];
                path[j] = minIndex;
            }
        }
    }

    return -1;
}

void reconstructPath(int* path, int sourceMember, int destinationMember) {
    if (path == NULL) {
        printf("Error: pointer cannot be NULL.\n");
        return;
    }

    if (sourceMember == destinationMember) {
        printf("%d", sourceMember);
        return;
    }

    if (path[destinationMember] == -1) {
        printf("Path does not exist.");
        return;
    }

    reconstructPath(path, sourceMember, path[destinationMember]);
    printf(" -> %d", destinationMember);
}

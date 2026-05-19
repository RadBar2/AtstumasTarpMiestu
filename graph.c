#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

weightedAdjacencyMatrix* createMatrix(int matrixSize) {
    weightedAdjacencyMatrix *matrix = (weightedAdjacencyMatrix*)malloc(sizeof(weightedAdjacencyMatrix));
    matrix->matrixSize = matrixSize;

    matrix->weight = (int**)malloc(matrixSize * sizeof(int*));
    for (int i = 0; i < matrixSize; ++i) {
        matrix->weight[i] = (int*)malloc(matrixSize * sizeof(int));
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
}

void reconstructPath(int* path, int sourceMember, int destinationMember) {
    if (path == NULL) {
        printf("Error: pointer cannot be NULL.\n");
        return;
    }

    if (sourceMember == destinationMember)
        printf("%d", sourceMember);
    else {
        reconstructPath(path, sourceMember, path[destinationMember]);
        printf(" -> %d", destinationMember);
    }
}

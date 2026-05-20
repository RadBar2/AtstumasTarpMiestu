#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

WeightedAdjacencyMatrix* create_matrix(int matrix_size) {
    WeightedAdjacencyMatrix *matrix = (WeightedAdjacencyMatrix*)malloc(sizeof(WeightedAdjacencyMatrix));
    if (matrix == NULL) {
        printf("Error: memory allocation failed.\n");
        return NULL;
    }

    matrix->matrix_size = matrix_size;

    matrix->weight = (int**)malloc(matrix_size * sizeof(int*));
    if (matrix->weight == NULL) {
        printf("Error: memory allocation failed.\n");
        return NULL;
    }
    for (int i = 0; i < matrix_size; ++i) {
        matrix->weight[i] = (int*)malloc(matrix_size * sizeof(int));
        if (matrix->weight[i] == NULL) {
        printf("Error: memory allocation failed.\n");
        return NULL;
    }
        for (int j = 0; j < matrix_size; ++j) {
            if (i != j)
                matrix->weight[i][j] = -1;
            else
                matrix->weight[i][j] = 0;
        }
    }

    return matrix;
}

void delete_matrix(WeightedAdjacencyMatrix* matrix) {
    if (matrix == NULL) {
        printf("Error: pointer cannot be NULL.\n");
        return;
    }

    for (int i = 0; i < matrix->matrix_size; ++i) {
        free(matrix->weight[i]);
    }
    free(matrix->weight);

    free(matrix);
}

void visualize(WeightedAdjacencyMatrix* matrix) {
    if (matrix == NULL) {
        printf("Error: pointer cannot be NULL.\n");
        return;
    }

    printf("      ");
    for (int j = 0; j < matrix->matrix_size; ++j) {
        printf("%5d", j);
    }
    printf("\n");

    for (int i = 0; i < matrix->matrix_size; ++i) {
        printf("%5d ", i);

        for (int j = 0; j < matrix->matrix_size; ++j)
            printf("%5d", matrix->weight[i][j]);
        printf("\n");
    }
}

int dijkstra(WeightedAdjacencyMatrix* matrix, int source_member, int destination_member, int* path) {
    if (matrix == NULL) {
        printf("Error: pointer cannot be NULL.\n");
        return -1;
    }

    int distances[matrix->matrix_size];
    bool visited[matrix->matrix_size];
    for (int i = 0; i < matrix->matrix_size; ++i) {
        if (i != source_member)
            distances[i] = -1;
        else
            distances[i] = 0;

        visited[i] = 0;
        path[i] = -1; // Possible error here, if the capacity of path[] array is smaller than the matrix_size
    }

    for (int i = 0; i < matrix->matrix_size; ++i) {
        int min_distance = -1;
        int min_index = -1;

        for (int j = 0; j < matrix->matrix_size; ++j) {
            if (distances[j] != -1 && !visited[j]) {
                if (min_distance == -1 || distances[j] < min_distance) {
                    min_distance = distances[j];
                    min_index = j;
                }
            }
        }

        if (min_index == -1)
            return -1;

        if (min_index == destination_member)
            return distances[min_index];

        visited[min_index] = 1;
        for (int j = 0; j < matrix->matrix_size; ++j) {
            if (matrix->weight[min_index][j] != -1 && !visited[j]
                    && (distances[j] > distances[min_index] + matrix->weight[min_index][j] || distances[j] == -1)) {
                distances[j] = distances[min_index] + matrix->weight[min_index][j];
                path[j] = min_index;
            }
        }
    }

    return -1;
}

void reconstruct_path(int* path, int source_member, int destination_member) {
    if (path == NULL) {
        printf("Error: pointer cannot be NULL.\n");
        return;
    }

    if (source_member == destination_member) {
        printf("%d", source_member);
        return;
    }

    if (path[destination_member] == -1) {
        printf("Path does not exist.");
        return;
    }

    reconstruct_path(path, source_member, path[destination_member]);
    printf(" -> %d", destination_member);
}

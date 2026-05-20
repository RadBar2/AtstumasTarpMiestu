#ifndef GRAPH_H_20260519
#define GRAPH_H_20260519

typedef struct {
    int matrix_size;
    int** weight;
} WeightedAdjacencyMatrix;

WeightedAdjacencyMatrix* create_matrix(int matrix_size);
void delete_matrix(WeightedAdjacencyMatrix* matrix);
void visualize(WeightedAdjacencyMatrix* matrix);
int dijkstra(WeightedAdjacencyMatrix* matrix, int source_member, int destination_member, int* path); // path[] array must be allocated with the matrix->matrixSize capacity
void reconstruct_path(int* path, int source_member, int destination_member); // it is unadvised to call reconstructPath() function when dijkstra() returns -1 (in other words, the path does not exist)

#endif // GRAPH_H_20260519

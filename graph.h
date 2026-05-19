#ifndef GRAPH_H_20260519
#define GRAPH_H_20260519

typedef struct {
    int matrixSize;
    int** weight;
} weightedAdjacencyMatrix;

weightedAdjacencyMatrix* createMatrix(int matrixSize);
void deleteMatrix(weightedAdjacencyMatrix* matrix);
void visualize(weightedAdjacencyMatrix* matrix);
int dijkstra(weightedAdjacencyMatrix* matrix, int sourceMember, int destinationMember, int* path); // path[] array must be allocated with the matrix->matrixSize capacity
void reconstructPath(int* path, int sourceMember, int destinationMember); // it is unadvised to call reconstructPath() function when dijkstra() returns -1 (in other words, the path does not exist)

#endif // GRAPH_H_20260519

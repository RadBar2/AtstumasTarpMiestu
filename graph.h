#ifndef GRAPH_H_20260519
#define GRAPH_H_20260519

typedef struct {
    int matrixSize;
    int** weight;
} weightedAdjacencyMatrix;

weightedAdjacencyMatrix* createMatrix(int matrixSize);
void deleteMatrix(weightedAdjacencyMatrix* matrix);
void visualize(weightedAdjacencyMatrix* matrix);
int dijkstra(weightedAdjacencyMatrix* matrix, int sourceMember, int destinationMember, int* path);
void reconstructPath(int* path, int sourceMember, int destinationMember);

#endif // GRAPH_H_20260519

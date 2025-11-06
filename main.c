#include <stdio.h>
#include <stdlib.h>

//heap functions

    typedef struct {
        int *arr;       
        int size;       
        int capacity;   
    } MaxHeap;

    MaxHeap* createMaxHeap(int capacity) {
        MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
        heap->arr = (int*)malloc(capacity * sizeof(int));
        heap->size = 0;
        heap->capacity = capacity;
        return heap;
    }

    int parent(int i) { return (i - 1) / 2; }
    int lChild(int i) { return (2 * i) + 1; }
    int rChild(int i) { return (2 * i) + 2; }

    void swap(int *a, int *b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }


    void heapUp(MaxHeap *heap, int index) {
        while (index > 0 && heap->arr[parent(index)] < heap->arr[index]) {
            swap(&heap->arr[parent(index)], &heap->arr[index]);
            index = parent(index);
        }
    }

    void heapDown(MaxHeap *heap, int index) {
        int largest = index;
        int left = lChild(index);
        int right = rChild(index);

        if (left < heap->size && heap->arr[left] > heap->arr[largest])
            largest = left;

        if (right < heap->size && heap->arr[right] > heap->arr[largest])
            largest = right;

        if (largest != index) {
            swap(&heap->arr[index], &heap->arr[largest]);
            heapDown(heap, largest);
        }
    }


    void insertHeap(MaxHeap *heap, int value) {
        if (heap->size == heap->capacity) {
            heap->capacity *= 2;
            heap->arr = (int*)realloc(heap->arr, heap->capacity * sizeof(int));
        }
        heap->arr[heap->size] = value;
        heap->size++;
        heapUp(heap, heap->size - 1);
    }

    int heap_pop(MaxHeap *heap) {
        if (heap->size <= 0) {
            printf("Heap is empty!\n");
            return -1;
        }

        int root = heap->arr[0];
        heap->arr[0] = heap->arr[heap->size - 1];
        heap->size--;
        heapDown(heap, 0);
        return root;
    }


    int heap_Max(MaxHeap *heap) {
        if (heap->size <= 0) {
            printf("Heap is empty!\n");
            return -1;
        }
        return heap->arr[0];
    }


    void heap_Display(MaxHeap *heap) {
        printf("Heap elements: ");
        for (int i = 0; i < heap->size; i++)
            printf("%d ", heap->arr[i]);
        printf("\n");
    }

    void freeHeap(MaxHeap *heap) {
        free(heap->arr);
        free(heap);
    }


//graph functions

    void dfs(int src,int adjmat[][100],int n,int *visit)
{
    visit[src]=1;
    printf("%d->",src);
    for(int j=0;j<n;j++)
    {
        if(adjmat[src][j]==1 && visit[j]==0)
            dfs(j,adjmat,n,visit);
    }
    
}

void DFS(int adjmat[][100],int n)
{
    int visit[n];
    for(int i=0;i<n;i++)
        visit[i]=0;
    for(int i=0;i<n;i++)
    {
        if(visit[i]==0)
            dfs(i,adjmat,n,visit);
    }
    printf("null\nreached a dead end");

}

typedef struct {
    int numVertices;
    int **adjMatrix; 
    int *visited;    
} Graph;

typedef struct {
    int *items;
    int front, rear, size;
} Queue;

Graph* createGraph() {
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    printf("Enter the number of vertices: ");
    scanf("%d",(graph->numVertices));
    int vertices;
    graph->numVertices = vertices;

    graph->adjMatrix = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        graph->adjMatrix[i] = (int*)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++)
            graph->adjMatrix[i][j] = 0; // init graph
    }

    // init visited graph
    graph->visited = (int*)malloc(vertices * sizeof(int));
    for (int i = 0; i < vertices; i++)
        graph->visited[i] = 0;

    return graph;
}
//undirected additon of edges
void addEdge(Graph *graph, int src, int dest) {
    if (src >= graph->numVertices || dest >= graph->numVertices || src < 0 || dest < 0) {
        printf("Invalid edge (%d, %d)\n", src, dest);
        return;
    }
    graph->adjMatrix[src][dest] =graph->adjMatrix[dest][src] = 1;
}

// Print the adjacency matrix
void printGraph(Graph *graph) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// ========== QUEUE FUNCTIONS (for BFS) ==========

Queue* createQueue(int size) {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->items = (int*)malloc(size * sizeof(int));
    q->front = 0;
    q->rear = -1;
    q->size = 0;
    return q;
}

int isEmpty(Queue *q) {
    return q->size == 0;
}

void enqueue(Queue *q, int value) {
    q->rear++;
    q->items[q->rear] = value;
    q->size++;
}

int dequeue(Queue *q) {
    int item = q->items[q->front];
    q->front++;
    q->size--;
    return item;
}

void freeQueue(Queue *q) {
    free(q->items);
    free(q);
}

// ========== BFS (Breadth First Search) ==========

void BFS(Graph *graph, int startVertex) {
    for (int i = 0; i < graph->numVertices; i++)
        graph->visited[i] = 0;

    Queue *q = createQueue(graph->numVertices);
    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);

    printf("BFS starting from vertex %d:\n", startVertex);

    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);
        printf("%d ", currentVertex);

        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->adjMatrix[currentVertex][i] == 1 && graph->visited[i] == 0) {
                graph->visited[i] = 1;
                enqueue(q, i);
            }
        }
    }

    printf("\n");
    freeQueue(q);
}

// ========== FREE MEMORY ==========

void freeGraph(Graph *graph) {
    for (int i = 0; i < graph->numVertices; i++)
        free(graph->adjMatrix[i]);
    free(graph->adjMatrix);
    free(graph->visited);
    free(graph);
}



int main() {
    
}

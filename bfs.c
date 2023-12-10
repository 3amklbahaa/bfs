#include <stdio.h>
#include <stdlib.h>
typedef struct graph{
    int vertices;
    int **adj_matrix;
}graph;
typedef struct queue{
    int first, last, size;
    unsigned capacity;
    int *array;
}queue;
graph* create_graph(int vertices){
    graph* graph =(struct graph *)malloc(sizeof(struct graph));
    graph->vertices=vertices;
    graph->adj_matrix = (int**)malloc(vertices * sizeof(int*));
    for(int i=0;i<vertices;i++){
        graph->adj_matrix[i]=(int *)malloc(vertices*sizeof(int));
        for(int j=0;j<vertices;j++){
            graph->adj_matrix[i][j]=0;
        }
    }
    return graph;
}
void Add_Edge(struct graph* graph,int src, int des){
    graph->adj_matrix[src][des]=1;
    graph->adj_matrix[des][src]=1;
}
struct queue * create_Queue(unsigned capacity){
    struct queue *queue = (struct queue *)malloc(sizeof(struct queue));
    queue->capacity=capacity;
    queue->first=queue->size=0;
    queue->last=capacity-1;
    queue->array=(int *)malloc(queue->capacity*sizeof(int));
    return queue;
}
int is_full(struct queue* queue){
    return (queue->size==queue->capacity);
}
int is_empty(struct queue* queue){
    return (queue->size==0);
}
void enqueue(struct queue *queue,int item){
    if(is_full(queue)){
        return;
    }
    queue->last = (queue->last+1) % queue->capacity;
    queue->array[queue->last]=item;
    queue->size=queue->size+1;
}
int dequeue(struct queue *queue){
    if(is_empty(queue)){
        return -1;
    }
    int item = queue->array[queue->first];
    queue->first=(queue->first+1)%queue->capacity;
    queue->size=queue->size-1;
    return item;
}
void bfs_with_queue(struct graph* graph, int start_vertex) {
    struct queue* queue = create_Queue(graph->vertices);
    int* visited = (int *)malloc(graph->vertices * sizeof(int));
    for (int i = 0; i < graph->vertices; i++) {
        visited[i] = 0;
    }
    enqueue(queue, start_vertex);
    visited[start_vertex] = 1;
    while (!is_empty(queue)) {
        int current_item = dequeue(queue);
        printf("%d ", current_item);
        for (int i = 0; i < graph->vertices; i++) {
            if (!visited[i] && graph->adj_matrix[current_item][i] == 1) {
                enqueue(queue, i);
                visited[i] = 1;
            }
        }
    }
    free(queue->array);
    free(queue);
    free(visited);
}
void free_graph(struct graph* graph){
    for(int i=0;i<graph->vertices;i++){
        free(graph->adj_matrix[i]);
    }
    free(graph->adj_matrix);
    free(graph);
}
int main() {
    int vertices = 6;
    struct graph* graph = create_graph(vertices);
    Add_Edge(graph, 0, 1);
    Add_Edge(graph, 0, 2);
    Add_Edge(graph, 1, 3);
    Add_Edge(graph, 1, 4);
    Add_Edge(graph, 2, 5);
    printf("BFS with Queue: ");
    bfs_with_queue(graph, 0);
    free_graph(graph);
    return 0;
}

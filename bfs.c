#include <stdio.h>
#include <stdlib.h>
void get_array(int **p,int N){
    printf("plz enter matrix: ");
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            scanf("%d",&p[i][j]);
        }
    }
}
void print_array(int **p, int N){
    printf("your matrix is : \n");
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            printf("%d",p[i][j]);
        }
        printf("\n");
    }
}
void bfs(int **p, int N, int *visited, int start){
    int front=0, Rear=0;
    int *q = (int *)malloc(N*sizeof(int));
    q[Rear++]=start;
    visited[start]=1;
    while(front!=Rear){
        int current = q[front++];
        printf("%d",current);
        for(int i=0;i<N;i++){
            if(p[current][i]==1&&!visited[i]){
                q[Rear++]=i;
                visited[i]=1;
            }
        }
    }
}
int main(){
    int **p, N, start, *visited;
    printf("plz enter N and start: ");
    scanf("%d%d",&N,&start);
    p =(int **)malloc(N*sizeof(int*));
    visited =(int *)malloc(N*sizeof(int));
    for(int i=0;i<N;i++){
        visited[i]=0;
    }
    for(int i=0;i<N;i++){
        p[i]=(int *)malloc(N*sizeof(int));
    }
    get_array(p,N);
    print_array(p,N);
    bfs(p,N,visited,start);
    return 0;
}

#include <stdio.h>
#include <stdbool.h>
#include <values.h>

#define V 5
int printMST(int parent[], int graph[10][10])
{
    printf(" Edge\n");
    for (int i = 1; i < V; i++)
        printf(" %d-%d \n", parent[i], i);
}
int minKey(int key[], bool mstSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}
void prim(int graph[V][V])
{
    int parent[V];
    int key[V];
    bool mstSet[V];
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;
    key[0] = 0;
    parent[0] = -1;
    for (int count = 0; count < V-1; count++)
    {
        int u = minKey(key, mstSet);
        mstSet[u] = true;
        for (int v = 0; v < V; v++)
            if (graph[u][v] && mstSet[v] == false && graph[u][v] <  key[v])
                parent[v]  = u, key[v] = graph[u][v];
    }
    printMST(parent, graph);
}
int minDistance(int dist[], bool sptSet[])
{
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}
int printSolution(int dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}
void dijkstra(int graph[V][V], int src)
{
    int dist[V];
    bool sptSet[V];
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
    dist[src] = 0;
    for (int count = 0; count < V-1; count++)
    {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u]+graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
    printSolution(dist, V);
}
int main()
{
    //int graph[9][9],i,m,j;
    printf("_______________\n Prim's Algorithm\n_______________\n");
    printf("Shortest spanning Tree:\n");
    //printf("Enter the distances between each pair of vertices:");
    /**for(i=0;i<V;i++)
    {printf("enter values for %d row\n", (i+1));
        for(j=0;j<V;j++){
            scanf("%d",graph[i][j]);
        }
    }**/
    int graph[V][V] = { { 0, 2, 0, 6, 0 }, { 2, 0, 3, 8, 5 },
                        { 0, 3, 0, 0, 3 }, { 6, 8, 0, 0, 9 }, { 0, 5, 7, 9, 0 }};
    int m;
    prim(graph);
    printf("_______________\n Dijsktra's Algorithm\n_______________\n");
    printf("Enter the source vertex:");
    scanf("%d",&m);
    dijkstra(graph,m);
    return 0;
}

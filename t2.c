#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "t2.h"
#define MAX_STRING_SIZE 100
#define MAX_GRAPH 10000

typedef struct Graph
{
    int graph_ar[MAX_GRAPH][MAX_GRAPH];
}Graph;

typedef struct Stops
{
    int stop_no;
    char Name[100];
    float Latitude;
    float Longitude;
}Stops;

typedef struct Edge
{
    int from;
    int to;
    int weight;
}Edge;

Stops *Vertexs[MAX_GRAPH];
Graph *g;

int next_field(FILE *f, char *buf, int max)
{
    int i = 0, end = 0, quoted = 0;

    for (;;)
    {
        buf[i] = fgetc(f);
        if (buf[i] == '"')
        {
            quoted = !quoted;
            buf[i] = fgetc(f);
        }
        if (buf[i] == ',' && !quoted)
        {
            break;
        }
        if (feof(f) || buf[i] == '\n')
        {
            end = 1;
            break;
        }
        if (i < max - 1)
        {
            ++i;
        }
    }

    buf[i] = 0; 
    return end;
}

Stops *fetch_stop(FILE *f)
{
    char buf[MAX_STRING_SIZE];
    Stops *temp_stop = malloc(sizeof(Stops));

    next_field(f, buf, MAX_STRING_SIZE); 
    temp_stop->stop_no = atoi(buf);
    next_field(f, temp_stop->Name, MAX_STRING_SIZE);
    next_field(f, buf, MAX_STRING_SIZE);
    temp_stop->Latitude = atof(buf);
    next_field(f, buf, MAX_STRING_SIZE);
    temp_stop->Longitude = atof(buf) ;

    return temp_stop;
}

Edge *fetch_edge(FILE *f)
{
    char buf[MAX_STRING_SIZE];
    Edge *temp_edge = malloc(sizeof(Stops));

    next_field(f, buf, MAX_STRING_SIZE); 
    temp_edge->from = atoi(buf);
    next_field(f, buf, MAX_STRING_SIZE); 
    temp_edge->to = atoi(buf);
    next_field(f, buf, MAX_STRING_SIZE); 
    temp_edge->weight = atoi(buf);

    return temp_edge;
}

void init_graph()
{
    g = malloc(sizeof(Graph));
    for (int i = 0; i < MAX_GRAPH; i++)
    {
        for (int j = 0; j < MAX_GRAPH; j++)
        {
            g->graph_ar[i][j] = 0;
        }
    }
}

void add_edge(Graph *g, int from, int to, int weight)
{
    g->graph_ar[from][to] = g->graph_ar[to][from] = weight;
}

int load_edges(char *fname)
{
    FILE *f;
    int from = 0;
    int to = 0;
    int weight;
    int num_edges = 0;

    f = fopen(fname, "r");
    if (!f)
    {
        printf("Unable to open %s\n", fname);
        return 0;
    }
    fetch_edge(f);
    init_graph();

    Edge *temp = malloc(sizeof(Edge));
    while (!feof(f))
    {
        temp = fetch_edge(f);
        from = temp->from;
        to = temp->to;
        weight = temp->weight;
        add_edge(g, from, to, weight);
        num_edges++;
    }

    fclose(f);
    free(temp);
    printf("Loaded %d edges\n", num_edges);

    return 1;
}

int load_vertices(char *fname)
{
    FILE *f;
    int num_vertices = 0;

    f = fopen(fname, "r");
    if (!f)
    {
        printf("Unable to open %s\n", fname);
        return 0;
    }
    fetch_stop(f);
    Stops *temp = malloc(sizeof(Stops));
    while (!feof(f))
    {
        temp = fetch_stop(f);
        Vertexs[temp->stop_no] = temp;
        num_vertices++;
    }
    fclose(f);
    free(temp);
    printf("Loaded %d vertices\n", num_vertices);

    return 1;
}

int min_distance(int distance[MAX_GRAPH], int shortestpath[MAX_GRAPH])
{
    int min = INT_MAX;
    int min_index;
    for (int j = 0; j < MAX_GRAPH; j++)
    {
        if (shortestpath[j] == 0 && distance[j] < min)
        {
            min = distance[j]; 
            min_index = j;
        }
    }
    return min_index;
}

void dijkstra(int start, int end)
{
    int distance[MAX_GRAPH], shortestpath[MAX_GRAPH], prev[MAX_GRAPH];
    
    for (int i = 0; i < MAX_GRAPH; i++)
    {
        distance[i] = INT_MAX; 
        shortestpath[i] = 0; 
        prev[i] = 0;
    }
    distance[end] = 0;

    for (int graph_size = 0; graph_size < MAX_GRAPH; graph_size++)
    {
        int min_index = min_distance(distance, shortestpath); 
        shortestpath[min_index] = 1;                     

        for (int Vertex = 0; Vertex < MAX_GRAPH; Vertex++)
        {
            if (!shortestpath[Vertex] && g->graph_ar[min_index][Vertex] && distance[min_index] != INT_MAX && distance[min_index] + g->graph_ar[min_index][Vertex] < distance[Vertex])
            {
                prev[Vertex] = min_index;
                distance[Vertex] = distance[min_index] + g->graph_ar[min_index][Vertex];
            }
        }
    }
    while (prev[start] != end)
    {
        printf("%d %s\n", Vertexs[prev[start]]->stop_no, Vertexs[prev[start]]->Name);
        start = prev[start];
    }
}

void shortest_path(int start, int end)
{
    printf("%d %s\n", Vertexs[start]->stop_no, Vertexs[start]->Name);
    dijkstra(start, end );
    printf("%d %s\n", Vertexs[end]->stop_no, Vertexs[end]->Name);
}

void free_memory(void)
{
    free(g);
}
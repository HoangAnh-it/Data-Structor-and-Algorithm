#include <iostream>
#include <limits.h>

using namespace std;

const int noVertex = 7;

int minDistance(int dist[], bool visited[])
{
    int min = INT_MAX;
    int min_index = 0;
    for (int i = 0; i < noVertex; i++)
    {
        if (visited[i] == false && dist[i] < min)
        {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}
void print(int dist[])
{
    for (int i = 0; i < noVertex; i++)
        cout << dist[i] << " ";
    cout << endl;
}

void Dijkstra(int graph[][noVertex], int src)
{
    int dist[noVertex];
    bool visited[noVertex];
    for (int i = 0; i < noVertex; i++)
    {
        dist[i] = INT_MAX;
        visited[i] = false;
    }
    dist[src] = 0;

    for (int i = 0; i < noVertex; i++)
    {
        int current = minDistance(dist, visited);
        visited[current] = true;
        for (int i = 0; i < noVertex; i++)
        {
            if (!visited[i] && graph[current][i] != 0 && dist[current] != INT_MAX && dist[current] + graph[current][i] < dist[i])
            {
                dist[i] = dist[current] + graph[current][i];
            }
        }
    }
    print(dist);
}

int main()
{
    int graph[noVertex][noVertex] = {{0, 1, 4, 0, 3, 0, 0}, {0, 0, 0, 2, 0, 0, 0}, {0, 0, 0, 0, 0, 2, 0}, {0, 0, 0, 0, 2, 0, 0}, {0, 0, 0, 2, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 3}, {0, 0, 0, 3, 0, 0, 0}};
    Dijkstra(graph, 0);
    return 0;
}
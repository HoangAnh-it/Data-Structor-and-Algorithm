#include <iostream>
#include <vector>
#include <map>
#include <limits.h>

using namespace std;

int V;

int minKey(int key[], bool visited[])
{
    int min_key = INT_MAX;
    int min_index = 0;
    for (int i = 0; i < V; i++)
    {
        if (!visited[i] && min_key > key[i])
        {
            min_key = key[i];
            min_index = i;
        }
    }

    return min_index;
}

void Prim(int dist[][20])
{
    int key[20];
    int path[20];
    bool visited[20];
    int end = 0;

    for (int i = 0; i < V; i++)
    {
        key[i] = INT_MAX;
        visited[i] = false;
        path[i] = 0;
    }
    path[0] = -1;
    key[0] = 0;
    for (int i = 0; i < V; i++)
    {
        int u = minKey(key, visited);
        visited[u] = true;
        if (u != 0)
        {
            path[u] = end;
        }
        end = u;
        for (int j = 0; j < V; j++)
        {
            if (!visited[j] && key[j] > dist[u][j] && dist[u][j] > 0)
            {
                key[j] = dist[u][j];
            }
        }
    }

    int way[20];
    int size = 0;
    int cur = end;
    while (cur != -1)
    {
        way[size++] = cur;
        cur = path[cur];
    }
    for (int i = size - 1; i >= 0; i--)
        cout << way[i] << " ";
    cout << endl;
}

int main()
{
    int edge;
    cin >> V >> edge;
    int dist[20][20];
    for (int i = 0; i < edge; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        dist[a][b] = c;
        dist[b][a] = c;
    }
    Prim(dist);
    return 0;
}
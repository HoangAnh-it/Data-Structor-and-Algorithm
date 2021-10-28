#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <limits.h>

using namespace std;

int V;

class Graph
{
private:
    map<int, bool> visited;
    map<int, vector<int>> adj;
    map<int, int> distance;
    int dist[100][100];
    int path[100];

public:
    Graph()
    {
        for (int i = 0; i < 10; i++)
            path[i] = 0;
        for (int i = 0; i < V; i++)
            distance[i] = INT_MAX;
    }

    void add(int v, int w, int d)
    {
        visited[v] = false;
        visited[w] = false;
        adj[v].push_back(w);
        adj[w].push_back(v);
        dist[v][w] = d;
        dist[w][v] = d;
    }

    int minDistance()
    {
        int min = INT_MAX;
        int min_index;
        for (auto x : distance)
        {
            if (x.second < min && visited[x.first] == false)
            {
                min = x.second;
                min_index = x.first;
            }
        }
        return min_index;
    }

    void dijkstra(int src)
    {
        distance[src] = 0;
        path[src] = -1;
        for (int i = 0; i < V; i++)
        {
            int cur = minDistance();
            visited[cur] = true;
            for (int i = 0; i < V; i++)
            {
                if (visited[i] == false && dist[cur][i] > 0 && distance[cur] + dist[cur][i] < distance[i])
                {
                    distance[i] = distance[cur] + dist[cur][i];
                    path[i] = cur;
                }
            }
        }
    }

    void trace_back(int src, int end)
    {
        int way[100];
        int size = 0;
        int cur = end;
        while (path[cur] != -1)
        {
            way[size++] = cur;
            cur = path[cur];
        }
        way[size++] = src;
        for (int i = size - 1; i >= 0; i--)
            cout << way[i] << " ";
    }

    int getMin(int v)
    {
        return distance[v];
    }

    void print_matrix()
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                cout << dist[i][j] << " ";
            }
            cout << endl;
        }
    }
};
int main()
{
    int n, X, Y;
    cin >> V >> n >> X >> Y;
    Graph g;
    for (int i = 0; i < n; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        g.add(a, b, c);
    }

    for (int i = 0; i < V; i++)
    {
        Graph _p = g;
        _p.dijkstra(i);
        for (int i = 0; i < V; i++)
            cout << _p.getMin(i);
        cout << endl;
    }

    return 0;
}
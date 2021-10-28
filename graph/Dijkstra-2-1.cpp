#include <iostream>
#include <map>
#include <vector>
#include <limits.h>

using namespace std;

int V;

class Graph
{
private:
    map<int, bool> visited;
    map<int, vector<int>> adj;
    map<int, int> minDistance;
    int dist[50][50];
    int path[50];

public:
    Graph() {}
    void add(int v, int w, int d)
    {
        visited[v] = false;
        visited[w] = false;
        adj[v].push_back(w);
        dist[v][w] = d;
        minDistance[v] = INT_MAX;
        minDistance[w] = INT_MAX;
    }

    int minDis()
    {
        int minDis = INT_MAX;
        int min_index = 0;
        for (int i = 0; i < V; i++)
        {
            if (visited[i] == false and minDistance[i] < minDis)
            {
                minDis = minDistance[i];
                min_index = i;
            }
        }
        return min_index;
    }

    void dijkstra(int src)
    {
        minDistance[src] = 0;
        path[src] = -1;
        for (int i = 0; i < V; i++)
        {
            int cur = minDis();
            visited[cur] = true;
            for (int j = 0; j < V; j++)
            {
                if (!visited[j] and dist[cur][j] > 0 and minDistance[cur] + dist[cur][j] < minDistance[j])
                {
                    minDistance[j] = minDistance[cur] + dist[cur][j];
                    path[j] = cur;
                }
            }
        }
    }

    void trace_back(int src, int end)
    {
        int way[50];
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
        cout << endl;
    }

    int getMinDistance(int v)
    {
        return minDistance[v];
    }
};

int main()
{
    Graph g;
    int v, X, Y;
    cin >> V >> v >> X >> Y;
    for (int i = 0; i < v; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        g.add(a, b, c);
    }
    g.dijkstra(X);
    cout << "Min " << g.getMinDistance(Y) << endl;
    g.trace_back(X, Y);
    return 0;
}
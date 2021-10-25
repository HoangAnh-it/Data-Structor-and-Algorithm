#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

const int V = 7;

class Graph
{
private:
    map<int, bool> visited;
    map<int, vector<int>> adj;
    int dist[V][V] = {0};
    int min[V];

public:
    Graph()
    {
        for (int i = 0; i < V; i++)
            min[i] = INT_MAX;
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                dist[i][j] = 0;
            }
        }
    }
    void add(int v, int w, int d)
    {
        visited[v] = false;
        adj[v].push_back(w);
        dist[v][w] = d;
    }

    void dijkstra(int src)
    {
        queue<int> q;
        q.push(src);
        min[src] = 0;
        while (!q.empty())
        {
            int current = q.front();
            q.pop();
            cout << min[current] << endl;
            for (int i = 0; i < adj[current].size(); i++)
            {
                int next = adj[current][i];
                if (dist[current][next] != 0 && min[next] > min[current] + dist[current][next])
                {
                    min[next] = min[current] + dist[current][next];
                }
                cout << "Push : " << next << " - min: " << min[next] << endl;
                q.push(next);
            }
        }
    }

    void print()
    {
        for (int i = 0; i < V; i++)
        {
            cout << min[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    Graph g;
    int n = 8;
    for (int i = 0; i < n; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        g.add(a, b, c);
    }
    g.dijkstra(0);
    g.print();
    return 0;
}
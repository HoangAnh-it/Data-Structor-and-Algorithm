#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Graph
{
private:
    map<int, bool> visited;
    map<int, vector<int>> adj;

public:
    void add(int v, int w)
    {
        visited[v] = false;
        visited[w] = false;
        adj[v].push_back(w);
        adj[w].push_back(v);
    }

    void DFS(int src)
    {
        visited[src] = true;
        cout << src << ' ';
        for (int i = 0; i < adj[src].size(); i++)
        {
            if (!visited[adj[src][i]])
                DFS(adj[src][i]);
        }
    }
};

int main()
{
    Graph g;
    int m, n;
    cin >> m >> n;
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        g.add(a, b);
    }
    int x;
    cin >> x;
    g.DFS(x);
    return 0;
}
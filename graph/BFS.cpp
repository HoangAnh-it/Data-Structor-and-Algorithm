#include <iostream>
#include <map>
#include <vector>
#include <queue>

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

    void BFS(int src)
    {
        queue<int> q;
        q.push(src);
        visited[src] = true;
        while (!q.empty())
        {
            int cur = q.front();
            cout << cur << " ";
            q.pop();
            for (int i = 0; i < adj[cur].size(); i++)
            {
                if (!visited[adj[cur][i]])
                {
                    q.push(adj[cur][i]);
                    visited[adj[cur][i]] = true;
                }
            }
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
    g.BFS(x);
    return 0;
}
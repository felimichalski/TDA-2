#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <numeric>
#define V 200

using namespace std;

int n;

int total_nodes;
vector<vector<int>> adj;

// Algoritmo obtenido de Geek for Geeks
bool bfs(int rGraph[V][V], int s, int t, int parent[])
{
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v=0; v<V; v++)
        {
            if (visited[v]==false && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return (visited[t] == true);
}

int maxflow(int graph[V][V], int s, int t)
{
    int u, v;

    int parent[V];

    int max_flow = 0;

    while (bfs(graph, s, t, parent))
    {
        int path_flow = INT_MAX;
        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, graph[u][v]);
        }

        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            graph[u][v] -= path_flow;
            graph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

int main() {
    int m;

    cin >> n >> m;

    vector<int> a_i(n);

    int total_in = 0;
    for (int i = 0; i < n; i++) {
        cin >> a_i[i];
        total_in += a_i[i];
    }

    total_nodes = n + 2;
    int capacity[V][V];
    adj.assign(total_nodes, vector<int>());

    int total_out = 0;
    for (int i = 0; i < n; i++) {
        int max;
        cin >> max;

        capacity[n][i] = a_i[i];
        capacity[i][i] = a_i[i];
        capacity[i][n + 1] = max;
        
        adj[i].push_back(i);
        adj[i].push_back(n);
        adj[i].push_back(n + 1);
        adj[n].push_back(i);
        adj[n + 1].push_back(i);
        
        total_out += max;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        capacity[u][v] = a_i[u];
        capacity[v][u] = a_i[v];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if(total_in > total_out) {
        cout << "NO" << endl;
        return 0;
    }

    int flow = maxflow(capacity, n, n + 1);
    
    if (flow == total_out) {
        cout << "YES" << endl;

        vector<vector<int>> moves(n, vector<int>(n, 0));

        for (int i = 0; i < n; i++) {
            moves[i][i] = a_i[i];
            for (int j : adj[i]) {
                if (j < n && j != i) {
                    moves[i][j] = max(a_i[i] - capacity[i][j], 0);
                    moves[i][i] -= moves[i][j];
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << moves[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        cout << "NO" << endl;
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <numeric>
using namespace std;

int n, total_nodes;
vector<vector<int>> capacity;
vector<vector<int>> adj;

// Algoritmo obtenido de cp-algorithm
int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INT_MAX});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(total_nodes);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
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
    capacity.assign(total_nodes, vector<int>(total_nodes, 0));
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

    int flow = maxflow(n, n + 1);

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

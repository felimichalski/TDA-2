#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_map>
#define MAX_NODES 200000
using namespace std;

int visited[MAX_NODES], discovery[MAX_NODES], low[MAX_NODES];
vector<pair<int, int>> graph[MAX_NODES];
vector<string> result(MAX_NODES, "none");

class UnionFind {
    int parent[MAX_NODES];

public:
    UnionFind(int n) {
        for(int i = 0; i < n; i++) parent[i] = i;
    }

    int findParent(int node) {
        return node == parent[node] ? node : parent[node] = findParent(parent[node]);
    }

    void unite(int u, int v) {
        int pu = findParent(u), pv = findParent(v);
        if (pu != pv) {
            parent[pv] = pu;
        }
    }
};

void dfs(int current, int parent_idx, int time) {
    visited[current] = 1; 
    discovery[current] = low[current] = ++time;
    
    for (const auto& [neighbor, idx] : graph[current]) {
        if (idx != parent_idx) {
            if (!visited[neighbor]) {
                dfs(neighbor, idx, time);
                low[current] = min(low[current], low[neighbor]);
                if(low[neighbor] > discovery[current]) {
                    result[idx] = "any";
                }
            }
            else {
                low[current] = min(low[current], low[neighbor]);
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    
    unordered_map<int, vector<tuple<int, int, int>>> edges_by_weight;

    UnionFind uf(n);

    for(int i = 1; i <= m; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        edges_by_weight[weight].push_back(make_tuple(u, v, i));
    }

    for(int weight = 1; weight <= 1000000; weight++) {
        for(const auto& [u, v, idx] : edges_by_weight[weight]) {
            int uParent = uf.findParent(u);
            int vParent = uf.findParent(v);
            if(uParent != vParent) {
                graph[uParent].push_back(make_pair(vParent, idx));
                graph[vParent].push_back(make_pair(uParent, idx));
                visited[uParent] = visited[vParent] = 0;
                result[idx] = "at least one";
            }
        }

        for(const auto& [u, v, idx] : edges_by_weight[weight]) {
            if(!visited[uf.findParent(u)]) {
                dfs(uf.findParent(u), -1, 0);
            }
            graph[uf.findParent(u)].clear();
            graph[uf.findParent(v)].clear();
            uf.unite(u, v);
        }
    }

    for(int i = 1; i <= m; i++) {
        cout << result[i] << '\n';
    }

    return 0;
}

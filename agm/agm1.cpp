#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <set>

using namespace std;

class UnionFind {
    vector<int> parent, rank;
public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        for(int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void setUnion(int u, int v) {
        int pu = find(u), pv = find(v);
        if(pu != pv) {
            if(rank[pu] < rank[pv]) swap(pu, pv);
            parent[pv] = pu;
            if(rank[pu] == rank[pv]) rank[pu]++;
        }
    }
};

struct Edge {
    int u, v, weight, idx;
    Edge(int u, int v, int w, int i) : u(u), v(v), weight(w), idx(i) {}
    Edge(int u, int v, int i) : u(u), v(v), weight(0), idx(i) {}
};

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

void dfs(int v, int p, vector<string>& result, vector<vector<pair<int, int>>>& adj, vector<bool>& visited, vector<int>& tin, vector<int>& low, int timer) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    for (auto [to, idx] : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v, result, adj, visited, tin, low, timer);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v]) {
                result[idx] = "any";
            }
        }
    }
}

void findBridges(int n, const vector<Edge>& edges, vector<string>& result, vector<int>& tin, vector<int>& low) {
    vector<vector<pair<int, int>>> adj;
    vector<bool> visited;
    visited.assign(n, false);
    adj.resize(n);

    unordered_map<pair<int, int>, int, pair_hash> edge_map;
    vector<int> toChange;

    for (const auto& edge : edges) {
        adj[edge.u].push_back({edge.v, edge.idx});
        adj[edge.v].push_back({edge.u, edge.idx});
        pair<int, int> edge_pair = {edge.u, edge.v};

        auto it = edge_map.find(edge_pair);
        if (it == edge_map.end()) {
            edge_map[edge_pair] = edge.idx;
        } else {
            toChange.push_back(edge.idx);
            toChange.push_back(it->second);
        }
    }

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i, -1, result, adj, visited, tin, low, 0);
        }
    }

    for (int idx : toChange) {
        result[idx] = "at least one";
    }
}

vector<string> solve(int n, vector<Edge>& edges) {
    vector<int> tin, low;
    tin.assign(n, -1);
    low.assign(n, -1);

    sort(edges.begin(), edges.end(), 
         [](const Edge& a, const Edge& b) { return a.weight < b.weight; });
    
    UnionFind uf(n);
    vector<string> result(edges.size(), "at least one");
    
    vector<vector<Edge>> sameWeightEdges;
    sameWeightEdges.reserve(edges.size());

    for(int i = 0; i < edges.size();) {
        int weight = edges[i].weight;
        vector<Edge> currentWeightEdges;
        
        while(i < edges.size() && edges[i].weight == weight) {
            int u = edges[i].u;
            int v = edges[i].v;
            int idx = edges[i].idx;
            if(uf.find(u) != uf.find(v)) {
                currentWeightEdges.emplace_back(uf.find(u), uf.find(v), idx);
            }
            else {
                result[idx] = "none";
            }
            i++;
        }
        
        if(currentWeightEdges.size() > 1) {
            findBridges(n, currentWeightEdges, result, tin, low);
        } else if(!currentWeightEdges.empty()) {
            result[currentWeightEdges[0].idx] = "any";
        }
        
        for(const auto& edge : currentWeightEdges) {
            uf.setUnion(edge.u, edge.v);
        }
    }
    
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    
    vector<Edge> edges;
    edges.reserve(m);
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if(u > v) {
            edges.emplace_back(u - 1, v - 1, w, i);
        } else {
            edges.emplace_back(v - 1, u - 1, w, i);
        }
    }
    
    vector<string> result = solve(n, edges);
    for(const string& aa : result) {
        cout << aa << "\n";
    }
    
    return 0;
}
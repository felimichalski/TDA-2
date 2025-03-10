#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_map>
#define MAX_NODES 200010
using namespace std;

class UnionFind {
    int parent[MAX_NODES];

public:
    UnionFind(int n) {
        for(int i = 0; i < n; i++) parent[i] = i;
    }

    int find_parent(int node) {
        return node == parent[node] ? node : parent[node] = find_parent(parent[node]);
    }

    void unite(int u, int v) {
        int pu = find_parent(u), pv = find_parent(v);
        if (pu != pv) {
            parent[pv] = pu;
        }
    }
};

void dfs(int current_node, int parent_edge_id, int& time_counter, vector<int>& visited, vector<int>& discovery_time, vector<int>& low_time, vector<int>& result, vector<vector<pair<int, int>>>& adjacency_list) {
    visited[current_node] = 1; 
    discovery_time[current_node] = low_time[current_node] = ++time_counter;
    
    for (const auto& [neighbor, idx] : adjacency_list[current_node]) {
        if (idx != parent_edge_id) {
            if (!visited[neighbor]) {
                dfs(neighbor, idx, time_counter, visited, discovery_time, low_time, result, adjacency_list);
                low_time[current_node] = min(low_time[current_node], low_time[neighbor]);
                result[idx] = 1 + (low_time[neighbor] > discovery_time[current_node]);
            }
            else {
                low_time[current_node] = min(low_time[current_node], low_time[neighbor]);
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    
    unordered_map<int, vector<tuple<int, int, int>>> edges_by_weight;
    for(int i = 1; i <= m; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        edges_by_weight[weight].push_back(make_tuple(u, v, i));
    }

    UnionFind uf(n);
    vector<int> visited(n, 0), result(m + 1, 0), discovery_time(n, 0), low_time(n, 0);
    vector<vector<pair<int, int>>> adjacency_list(n);

    // Al procesar los bordes por peso
    for(int weight = 1; weight <= 1000000; weight++) {
        // Añadir los bordes a la lista de adyacencia si no están conectados
        for(const auto& [u, v, idx] : edges_by_weight[weight]) {
            int uParent = uf.find_parent(u);
            int vParent = uf.find_parent(v);
            if(uParent != vParent) {
                adjacency_list[uParent].push_back(make_pair(vParent, idx));
                adjacency_list[vParent].push_back(make_pair(uParent, idx));
                visited[uParent] = visited[vParent] = 0;
                result[idx] = 1;
            }
        }

        // Realizar DFS para cada componente conexa
        for(const auto& [u, v, idx] : edges_by_weight[weight]) {
            int uParent = uf.find_parent(u);
            if (!visited[uParent]) {
                int time_counter = 0;  // Iniciar un contador de tiempo para DFS
                dfs(uParent, -1, time_counter, visited, discovery_time, low_time, result, adjacency_list);
            }

            // Limpiar las listas de adyacencia para estos nodos
            adjacency_list[uf.find_parent(u)].clear();
            adjacency_list[uf.find_parent(v)].clear();

            // Unir los nodos en la estructura de UnionFind
            uf.unite(u, v);
        }
    }

    // Imprimir los resultados
    for(int i = 1; i <= m; i++) {
        if(result[i] == 0) cout << "none";
        else if(result[i] == 1) cout << "at least one";
        else if(result[i] == 2) cout << "any";
        cout << '\n';
    }

    return 0;
}

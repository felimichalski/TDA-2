#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

vector<int> dijkstra(const unordered_map<int, vector<pair<int, int>>>& graph, int start, int n) {
    vector<int> distances(n, INT_MAX);
    distances[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int current_distance = pq.top().first;
        int current_node = pq.top().second;
        pq.pop();

        if (current_distance > distances[current_node]) continue;

        for (const auto& neighbor : graph.at(current_node)) {
            int next_node = neighbor.first;
            int weight = neighbor.second;
            int new_distance = current_distance + weight;

            if (new_distance < distances[next_node]) {
                distances[next_node] = new_distance;
                pq.push({new_distance, next_node});
            }
        }
    }

    return distances;
}

int main() {
    int n, m;
    cin >> n >> m;

    unordered_map<int, vector<pair<int, int>>> graph;

    for (int i = 0; i < m; i++) {
        int v, w, c;
        cin >> v >> w >> c;
        graph[v].push_back({w, c});
        graph[w].push_back({v, c});
    }

    vector<int> dist_start = dijkstra(graph, 0, n);
    vector<int> dist_end = dijkstra(graph, n - 1, n);

    int min_distance = dist_start[n - 1];
    int result = 0;

    for (int i = 0; i < n; i++) {
        for (const auto& edge : graph[i]) {
            int w = edge.first;
            int c = edge.second;
            if (dist_start[i] + c + dist_end[w] == min_distance) {
                result += c * 2;
            }
        }
    }

    cout << result << endl;
    return 0;
}

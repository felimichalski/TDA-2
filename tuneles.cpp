#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <sstream>

using namespace std;

map<int, int> findMinPaths(vector<vector<int>>& graph) {
    map<int, int> res;
    queue<pair<int, int>> queue;
    queue.push({1, 0});
    vector<bool> visited(graph.size(), false);

    while (!queue.empty()) {
        auto [current, level] = queue.front();
        queue.pop();

        if (!visited[current]) {
            visited[current] = true;
            res[current] = level;

            for (int neighbor : graph[current]) {
                if (!visited[neighbor]) {
                    queue.push({neighbor, level + 1});
                }
            }
        }
    }
    return res;
}

vector<vector<int>> buildGraph(int nodes) {
    vector<vector<int>> graph(nodes + 1);
    for (int i = 1; i <= nodes; ++i) {
        int tunnel;
        cin >> tunnel;
        graph[i].push_back(tunnel);
        if (i > 1) {
            graph[i - 1].push_back(i);
            graph[i].push_back(i - 1);
        }
    }
    return graph;
}

int main() {
    int nodes;
    cin >> nodes;

    vector<vector<int>> graph = buildGraph(nodes);

    map<int,int> minPaths = findMinPaths(graph);

    ostringstream output;
    for (int i = 1; i <= nodes; ++i) {
        output << minPaths[i] << " ";
    }

    cout << output.str() << endl;
    return 0;
}

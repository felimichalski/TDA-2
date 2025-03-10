#include <iostream>
#include <vector>
#include <map>
#include <stack>
using namespace std;

map<int, vector<int>> buildGraph(int nodes) {
    map<int, vector<int>> graph;
    for (int i = 0; i < nodes - 1; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    return graph;
}

pair<vector<int>, vector<int>> getGraphGroups(map<int, vector<int>>& graph) {
    map<int, int> visited;
    vector<int> group0, group1;
    stack<int> stack;

    for (const auto& node : graph) {
        if (visited.find(node.first) == visited.end()) {
            visited[node.first] = 0;
            group0.push_back(node.first);
            stack.push(node.first);

            while (!stack.empty()) {
                int current = stack.top();
                stack.pop();
                
                for (const auto& neighbor : graph[current]) {
                    if (visited.find(neighbor) == visited.end()) {
                        stack.push(neighbor);
                        int neighborNumber = 1 - visited[current];
                        visited[neighbor] = neighborNumber;
                        if (neighborNumber == 0)
                            group0.push_back(neighbor);
                        else
                            group1.push_back(neighbor);
                    }
                }
            }
        }
        break; // since is a tree i can asume that is a connected graph so i only need a single iteration of this for to get some node to start with
    }
    return {group0, group1};
}

int main() {
    int nodes;
    cin >> nodes;
    auto graph = buildGraph(nodes);

    auto [group0, group1] = getGraphGroups(graph);
    long long res = group0.size() * group1.size() - (nodes - 1); // total possible edges of the graph minus those already used

    cout << res << endl;
    return 0;
}

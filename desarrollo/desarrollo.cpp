#include <iostream>
#include <vector>
using namespace std;

int main(){
    long long n;
    cin >> n;
    vector<vector<long long>> dist(n, vector<long long>(n));

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> dist[i][j];
    vector<long long> order(n);

    for(int i = 0; i < n; i++) {
        cin >> order[i];
        order[i]--;
    }

    vector<bool> active_nodes(n);
    string res = "";

    for(int k = n - 1; k >= 0; k--) {
        long long sum = 0;
        int cur_node = order[k];
        active_nodes[cur_node] = true;
        
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][cur_node] + dist[cur_node][j]);
                if(active_nodes[i] && active_nodes[j]) sum += dist[i][j];
            }
        }
        
        res = to_string(sum) + res;
        if(k != 0) res = " " + res;
    }
    
    cout << res << endl;
    return 0;
}
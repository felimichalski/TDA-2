#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int test_cases;
    cin >> test_cases;

    for (int t = 0; t < test_cases; t++) {
        int activities;
        cin >> activities;

        vector<pair<int, int> > pairs;
        for (int i = 0; i < activities; i++) {
            int start, end;
            cin >> start >> end;
            pairs.push_back(make_pair(start, end));
        }

        sort(pairs.begin(), pairs.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
            return a.second < b.second;
        });

        vector<pair<int, int> > solution;
        if(pairs.size() > 0) {
            solution.push_back(pairs[0]);

            for (size_t i = 1; i < pairs.size(); i++) {
                if (solution.back().second <= pairs[i].first) {
                    solution.push_back(pairs[i]);
                }
            }
        }

        cout << solution.size();
        cout << endl;
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool canAssign(int cows, const vector<int>& positions, int distance) {
    int lastPos = positions[0];
    cows--;

    for (int i = 1; i < positions.size(); i++) {
        if (lastPos + distance <= positions[i]) {
            lastPos = positions[i];
            cows--;
            if (cows == 0) {
                return true;
            }
        }
    }

    return false;
}

int calc(int cows, const vector<int>& positions, int minVal, int maxVal) {
    int half = (minVal + maxVal) / 2;

    if (canAssign(cows, positions, half)) {
        if (minVal >= maxVal) {
            return half;
        } else {
            return calc(cows, positions, half + 1, maxVal);
        }
    } else {
        return calc(cows, positions, minVal, half - 1);
    }
}

int main() {
    int testCases;
    cin >> testCases;

    while (testCases--) {
        int n, c;
        cin >> n >> c;

        vector<int> stalls(n);
        for (int i = 0; i < n; i++) {
            cin >> stalls[i];
        }

        sort(stalls.begin(), stalls.end());

        int minPos = stalls[0];
        int maxPos = stalls[n - 1];

        int maxDistance = maxPos - minPos;

        int result = calc(c, stalls, 1, maxDistance);

        cout << result << endl;
    }

    return 0;
}

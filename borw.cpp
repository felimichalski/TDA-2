#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

int n;
long int sequence[201];
int dp[201][201][201];
vector<tuple<int, int, int>> modifiedIndices;

bool canBePaintedWhite(int current, int candidate) {
    return candidate > n || sequence[current] > sequence[candidate];
}

bool canBePaintedBlack(int current, int candidate) {
    return candidate > n || sequence[current] < sequence[candidate];
}

void initializeTensor() {
    for (int i = 0; i < 201; i++) {
        for (int j = 0; j < 201; j++) {
            for (int k = 0; k < 201; k++) {
                dp[i][j][k] = 0;
            }
        }
    }
}

int calculateMiniumWithoutPainting() {    
    for(int current = 1; current <= n; current++) {
        for(int lastBlack = current + 1; lastBlack <= n + 1; lastBlack++) {
            for(int lastWhite = current + 1; lastWhite <= n + 1; lastWhite++) {
                dp[current][lastBlack][lastWhite] = dp[current - 1][lastBlack][lastWhite] + 1;
                
                if(canBePaintedWhite(current, lastWhite)) {
                    dp[current][lastBlack][lastWhite] = min(dp[current][lastBlack][lastWhite], dp[current - 1][lastBlack][current]);
                }

                if(canBePaintedBlack(current, lastBlack)) {
                    dp[current][lastBlack][lastWhite] = min(dp[current][lastBlack][lastWhite], dp[current - 1][current][lastWhite]);
                }

                if(dp[current][lastBlack][lastWhite] != 0) modifiedIndices.emplace_back(current, lastBlack, lastWhite);
            }
        }
    }

    return dp[n][n + 1][n + 1];
}

void resetTensor() {
    for (const auto& index : modifiedIndices) {
        int i, j, k;
        tie(i, j, k) = index;
        dp[i][j][k] = 0;
    }
    modifiedIndices.clear();
}

int main() {
    initializeTensor();
    while(cin >> n) {
        if(n == -1) break;

        for(int i = 1; i <= n; i++) {
            cin >> sequence[i];
        }

        int res = calculateMiniumWithoutPainting();

        resetTensor();
        
        cout << res << endl;
    }

    return 0;
}

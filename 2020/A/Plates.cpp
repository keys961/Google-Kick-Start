#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

void solve(int case_id, int sums[][31], int x, int y, int p) {
    int dp[x + 1][p + 1]; // dp(i)(j): pick j plates from last i stacks
    for(int i = 0; i <= p; i++) {
        dp[0][i] = 0;
    }
    for(int i = 0; i <= x; i++) {
        dp[i][0] = 0;
    }
    for(int i = 1; i <= x; i++) {
        // pick prev i stacks
        for(int j = 1; j <= p; j++) {
            dp[i][j] = 0;
            int max_pick = min(j, y);
            for(int k = 0; k <= max_pick; k++) {
                dp[i][j] = max(dp[i][j], sums[i][k] + dp[i - 1][j - k]);
            }
        }
    }
    cout << "Case #" << case_id << ": " << dp[x][p] << endl;
}

int main() {
    int t = 0;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int n, k, p;
        cin >> n >> k >> p;
        int plates[n][k];
        int sum[51][31];
        for(int y = 0; y <= k; y++) {
            sum[0][y] = 0;
        }
        for(int x = 1; x <= n; x++) {
            sum[x][0] = 0;
            for(int y = 1; y <= k; y++) {
                cin >> plates[x - 1][y - 1];
                sum[x][y] = sum[x][y - 1] + plates[x - 1][y - 1];
            }
        }
        solve(i, sum, n, k, p);
    }
    return 0;
}


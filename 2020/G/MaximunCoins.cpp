#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <map>

using namespace std;

void solve(int case_id, vector<vector<long long>>& matrix) {
    vector<long long> prev = vector<long long>(matrix.size());
    long long ans = 0;
    for(int i = 0; i < matrix.size(); i++) {
        prev[i] = matrix[0][i];
        ans = max(ans, prev[i]);
    }
    vector<long long> cur = vector<long long>(matrix.size());
    for(int row = 1; row < matrix.size(); row++) {
        for(int col = 0; col < matrix[row].size(); col++) {
            if(col == 0) {
                cur[col] = matrix[row][col];
            } else {
                cur[col] = matrix[row][col] + prev[col - 1];
            }
            ans = max(ans, cur[col]);
        }
        cur.swap(prev);
    }
    cout << "Case #" << case_id << ": " << ans << endl;
}

int main() {
    int t = 0;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int n;
        cin >> n;
        vector<vector<long long>> arr(n, vector<long long>(n));
        for(int r = 0; r < n; r++) {
            for(int c = 0; c < n; c++) {
                cin >> arr[r][c];
            }
        }
        solve(i, arr);
    }
    return 0;
}


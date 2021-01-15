#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <map>
#include <cmath>

using namespace std;

double dfs(int i, int j, vector<vector<double>>& kdp) {
    if(i == 1) {
        return 0.0;
    }
    if(i == 2) {
        kdp[i][j] = 1.0;
        return 1.0;
    }

    if(kdp[i][j] > 0) {
        return kdp[i][j];
    }
    double ans;
    if(j == 1 || i == j) {
        ans = 1.0;
    } else {
        ans = 2.0;
    }

    int moved_cnt = j - 1;
    if(moved_cnt > 0) {
        ans += moved_cnt * dfs(i - 1, j - 1, kdp);
    }
    if(i - moved_cnt - 1 > 0) {
        ans += (i - moved_cnt - 1) * dfs(i - 1, j, kdp);
    }
    ans /= (i * 1.0 - 1);
    kdp[i][j] = ans;
    return ans;
}

void solve(int case_id, vector<long long>& arr) {
    double score = 0.0;
    vector<vector<double>> kdp = vector<vector<double>>(arr.size() + 1, vector<double>(arr.size() + 1));
    for(int i = 1; i <= arr.size(); i++) {
        double coefficient = dfs(arr.size(), i, kdp);
        score += arr[i - 1] * coefficient;
    }
    printf("Case #%d: %.6f\n", case_id, score);
}

int main() {
    int t = 0;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int n;
        cin >> n;
        vector<long long> arr(n);
        for(int j = 0; j < n; j++) {
            cin >> arr[j];
        }
        solve(i, arr);
    }
    return 0;
}


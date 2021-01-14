#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <map>
#include <cmath>

using namespace std;

void dfs(vector<long long>& arr, double cur_score, double& total_score, double& times) {
    if (arr.size() == 2) {
        cur_score += arr[0] + arr[1];
        total_score += cur_score;
        times += 1;
        return;
    }

    for(int i = 0; i < arr.size() - 1; i++) {
        vector<long long> new_arr(arr.size() - 1);
        for(int j = 0; j < i; j++) {
            new_arr[j] = arr[j];
        }
        new_arr[i] = arr[i] + arr[i + 1];
        for(int j = i + 2; j < arr.size(); j++) {
            new_arr[j - 1] = arr[j];
        }
        dfs(new_arr, cur_score +  arr[i] + arr[i + 1], total_score, times);
    }
}

void solve(int case_id, vector<long long>& arr) {
    double total_score = 0.0;
    double times = 0.0;
    dfs(arr, 0, total_score, times);
    printf("Case #%d: %.6f\n", case_id, total_score / times);
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


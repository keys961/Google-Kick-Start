#include <iostream>
#include <vector>

using namespace std;

int get_min(vector<vector<int>>& dp, int i, int start, int end) {
    int ret = INT32_MAX;
    for(int conv = start; conv <= end; conv++) {
        ret = min(ret, dp[i][conv]);
    }
    return ret;
}

void solve(int case_id, vector<int>& arr) {
    vector<vector<int>> dp = vector<vector<int>>(arr.size() + 1, vector<int>(4, 0));

    for(int i = arr.size() - 2; i >= 0; i--) {
        for(int cur_conv = 0; cur_conv < 4; cur_conv++) {
            if(arr[i] == arr[i + 1]) {
                dp[i][cur_conv] = dp[i + 1][cur_conv];
            } else {
                if(arr[i] > arr[i + 1]) {
                    if(cur_conv == 0) {
                        dp[i][cur_conv] = 1 + get_min(dp, i + 1, 0, 3);
                    } else {
                        dp[i][cur_conv] = get_min(dp, i + 1, 0, cur_conv - 1);
                    }
                } else {
                    if(cur_conv == 3) {
                        dp[i][cur_conv] = 1 + get_min(dp, i + 1, 0, 3);
                    } else {
                        dp[i][cur_conv] = get_min(dp, i + 1, cur_conv + 1, 3);
                    }
                }
            }
        }
    }
    cout << "Case #" << case_id << ": " << get_min(dp, 0, 0, 3) << endl;
}

int main() {
    int t = 0;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int k;
        cin >> k;
        vector<int> arr(k, 0);
        for(int j = 0; j < k; j++) {
            cin >> arr[j];
        }
        solve(i, arr);
    }
    return 0;
}


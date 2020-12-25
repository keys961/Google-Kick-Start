#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>

using namespace std;

long long count(unordered_map<int, int>& prefix_sum, int min, int max, int sum) {
    long long ans = 0;
    int range_min = std::max(0, sum - max);
    int range_max = sum - min;
    for(int i = (int)sqrt(range_min); i * i <= range_max; i++) {
        int target = i * i;
        int to_find = sum - target;
        ans += prefix_sum[to_find];
    }
    return ans;
}

void solve(int case_id, vector<int>& arr) {
    unordered_map<int, int> prefix_sum;
    int min = 0;
    int max = 0;
    prefix_sum[0] = 1;
    int sum = 0;
    long long ans = 0;
    for(int n : arr) {
        sum += n;
        ans += count(prefix_sum, min, max, sum);
        min = std::min(min, sum);
        max = std::max(max, sum);
        prefix_sum[sum] += 1;
    }
    cout << "Case #" << case_id << ": " << ans << endl;
}

int main() {
    int t = 0;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int n;
        cin >> n;
        vector<int> arr(n, 0);
        for(int j = 0; j < n; j++) {
            cin >> arr[j];
        }
        solve(i, arr);
    }
    return 0;
}


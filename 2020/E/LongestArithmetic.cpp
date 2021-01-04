#include <iostream>
#include <vector>

using namespace std;

void solve(int case_id, vector<int>& arr) {
    int prev_diff = arr[1] - arr[0];
    int ans = 2;
    int len = 2;
    for(int i = 2; i < arr.size(); i++) {
        int diff = arr[i] - arr[i - 1];
        if(diff == prev_diff) {
            len += 1;
            ans = max(ans, len);
        } else {
            len = 2;
        }
        prev_diff = diff;
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


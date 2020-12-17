#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

bool is_valid(vector<int>& sessions, int max_diff, int k) {
    int cnt = 0;
    for(int i = 1; i < sessions.size(); i++) {
        int diff = sessions[i] - sessions[i - 1];
        cnt += diff / max_diff;
        if(diff % max_diff == 0) {
            cnt -= 1;
        }
        if(cnt > k) {
            return false;
        }
    }
    return true;
}

void solve(int case_id, int n, int k) {
    vector<int> sessions(n, 0);
    int max_diff = 0;
    for(int i = 0; i < n; i++) {
        cin >> sessions[i];
        if (i > 0) {
            max_diff = max(max_diff, sessions[i] - sessions[i - 1]);
        }
    }
    int ans = max_diff;
    int left = 1;
    int right = max_diff;
    while(left <= right) {
        int mid = (left + right) / 2;
        if(is_valid(sessions, mid, k)) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    cout << "Case #" << case_id << ": " << ans << endl;
}

int main() {
    int t = 0;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int n, k;
        cin >> n >> k;
        solve(i, n, k);
    }
}


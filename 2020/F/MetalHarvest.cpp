#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve(int case_id, vector<pair<int, int>>& intervals, int k) {
    sort(intervals.begin(), intervals.end());
    int ans = 0;
    int i = 0;
    int cursor = intervals[0].first;
    while (i < intervals.size()) {
        if(intervals[i].second - cursor < k) {
            // extend
            int next_i = i + 1;
            for (; next_i < intervals.size(); next_i++) {
                if(intervals[next_i].second - cursor > k) {
                    break;
                }
            }
            cursor = max(intervals[next_i].first, cursor + k);
            ans += 1;
            i = next_i;
        } else {
            // not extend
            int cnt = (intervals[i].second - cursor) / k;
            ans += cnt;
            cursor += cnt * k;
            if(cursor == intervals[i].second) {
                if(i < intervals.size() - 1) {
                    cursor = intervals[i + 1].first;
                }
                i += 1;
            }
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
        vector<pair<int, int>> intervals;
        for(int j = 0; j < n; j++) {
            int s, e;
            cin >> s >> e;
            intervals.emplace_back(s, e);
        }
        solve(i, intervals, k);
    }
    return 0;
}


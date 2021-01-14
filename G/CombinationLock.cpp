#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <map>
#include <cmath>

using namespace std;

void solve(int case_id, vector<long long>& wheels, long long w, long long n) {
    sort(wheels.begin(), wheels.end());
    vector<long long> prefix_sum = vector<long long>(w + 1);
    for(int i = 1; i <= w; i++) {
        prefix_sum[i] = prefix_sum[i - 1] + wheels[i];
    }
    long long ans = INT64_MAX;
    for(int i = 1; i <= w; i++) {
        long long left_margin = wheels[i] - (n + 1) / 2;
        long long right_margin = wheels[i] + (n + 1) / 2;

        int left = upper_bound(wheels.begin(), wheels.end(), left_margin) - wheels.begin();
        if(left > 0 && wheels[left] > left_margin) {
            left--;
        }
        int right = lower_bound(wheels.begin(), wheels.end(), right_margin) - wheels.begin();
        if(right <= w && wheels[right] < right_margin) {
            right++;
        }

        long long move = 0;
        // not round left
        move += (i - left - 1) * wheels[i] - (prefix_sum[i - 1] - prefix_sum[left]);
        // not round right
        move += prefix_sum[right - 1] - prefix_sum[i] - (right - i - 1) * wheels[i];
        // round left
        move += prefix_sum[left] + n * left - left * wheels[i];
        // round right
        move += (w - right + 1) * (wheels[i] + n) - (prefix_sum[w] - prefix_sum[right - 1]);
        ans = min(ans, move);
    }

    cout << "Case #" << case_id << ": " << ans << endl;
}

int main() {
    int t = 0;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        long long w, n;
        cin >> w >> n;
        vector<long long> wheels(w + 1);
        for(int j = 0; j < w; j++) {
            cin >> wheels[j + 1];
        }
        solve(i, wheels, w, n);
    }
    return 0;
}


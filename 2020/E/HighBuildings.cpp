#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve(int case_id, int n, int a, int b, int c) {
    if(a + b - c > n) {
        cout << "Case #" << case_id << ": " << "IMPOSSIBLE" << endl;
        return;
    }
    if(a == 1 && b == 1 && c == 1 && n != 1) {
        cout << "Case #" << case_id << ": " << "IMPOSSIBLE" << endl;
        return;
    }
    bool rev = false;
    if(a > b) {
        swap(a, b);
        rev = true;
    }
    vector<int> ans(n, 0);
    // 1. split peak evenly to 2 sides
    int peak_cnt = c;
    int left_peak_start = a - c;
    int right_peak_start = (n - 1) - (b - c);
    int i = left_peak_start;
    int j = right_peak_start;
    bool flag = true;
    while (peak_cnt-- > 0) {
        if(flag) {
            ans[i++] = n;
        } else {
            ans[j--] = n;
        }
        flag = !flag;
    }
    // 2. fill the inner 1
    while(i <= j) {
        ans[i++] = 1;
    }
    // 3. fill left part
    for(i = left_peak_start - 1; i >= 0; i--) {
        ans[i] = n - 1;
    }
    // 4. fill right part
    for(i = right_peak_start + 1; i < n; i++) {
        ans[i] = n - 1;
    }
    if(rev) {
        reverse(ans.begin(), ans.end());
    }
    cout << "Case #" << case_id << ":";
    for(int height : ans) {
        cout << " " << height;
    }
    cout << endl;
}

int main() {
    int t = 0;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int n, a, b, c;
        cin >> n >> a >> b >> c;
        solve(i, n, a, b, c);
    }
    return 0;
}


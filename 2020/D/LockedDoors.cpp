#include <iostream>
#include <vector>

using namespace std;

int query(vector<int>& locks, int s, int q) {
    s -= 1;
    int ans = s;
    int left = s;
    int right = s;
    while(--q > 0) {
        if(left == 0) {
            right += 1;
            ans = right;
        } else if(right == locks.size()) {
            left -= 1;
            ans = left;
        } else {
            if(locks[left - 1] < locks[right]) {
                left -= 1;
                ans = left;
            } else {
                right += 1;
                ans = right;
            }
        }
    }
    return ans + 1;
}

void solve(int case_id, vector<int>& locks, int q) {
    vector<int> ans(q, 0);
    for(int i = 0; i < q; i++) {
        int s, k;
        cin >> s >> k;
        ans[i] = query(locks, s, k);
    }
    cout << "Case #" << case_id << ":";
    for(int n : ans) {
        cout << " " << n;
    }
    cout << endl;
}

int main() {
    int t = 0;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int n, q;
        cin >> n >> q;
        vector<int> locks(n - 1, 0);
        for(int j = 0; j < n - 1; j++) {
            cin >> locks[j];
        }
        solve(i, locks, q);
    }
    return 0;
}


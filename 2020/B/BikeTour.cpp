#include <iostream>
#include <vector>

using namespace std;

void solve(int case_id, vector<int>& checkpoints) {
    int ans = 0;
    for(int i = 1; i < checkpoints.size() - 1; i++) {
        if(checkpoints[i] > checkpoints[i - 1] && checkpoints[i + 1] < checkpoints[i]) {
            ans += 1;
        }
    }
    cout << "Case #" << case_id << ": " << ans << endl;
}

int main() {
    int t = 0;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int n;
        cin >> n;
        vector<int> checkpoints(n, 0);
        for(int j = 0; j < n; j++) {
            cin >> checkpoints[j];
        }
        solve(i, checkpoints);
    }
    return 0;
}


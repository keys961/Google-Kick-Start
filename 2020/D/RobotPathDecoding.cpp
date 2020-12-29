#include <iostream>
#include <vector>

using namespace std;

void solve(int case_id, vector<int>& arr) {
    int prev_max = -1;
    int ans = 0;
    for(int i = 0; i < arr.size(); i++) {
        int n = arr[i];
        if(n > prev_max) {
            prev_max = n;
            if(!(i < arr.size() - 1 && arr[i] <= arr[i + 1])) {
                ans += 1;
            }
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
        vector<int> arr(n, 0);
        for(int j = 0; j < n; j++) {
            cin >> arr[j];
        }
        solve(i, arr);
    }
    return 0;
}



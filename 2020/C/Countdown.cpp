#include <iostream>
#include <vector>

using namespace std;

void solve(int case_id, vector<int>& arr, int k) {
    int cnt = 0;
    int i = 0;
    while(i < arr.size()) {
        if(arr[i] == k) {
            // check
            int j = i + 1;
            while (j < arr.size() && j < i + k) {
                if(arr[j] + 1 == arr[j - 1]) {
                    j += 1;
                } else {
                    break;
                }
            }
            if(arr[j - 1] == 1) {
                cnt += 1;
            }
            i = j;
        } else {
            i += 1;
        }
    }
    cout << "Case #" << case_id << ": " << cnt << endl;
}

int main() {
    int t = 0;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int n, k;
        cin >> n >> k;
        vector<int> arr(n, 0);
        for(int j = 0; j < n; j++) {
            cin >> arr[j];
        }
        solve(i, arr, k);
    }
    return 0;
}


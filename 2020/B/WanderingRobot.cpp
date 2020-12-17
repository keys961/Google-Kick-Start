#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double cal(vector<double>& log_2_factorials, int w_step, int h_step) {
    int steps = w_step + h_step;
    return pow(2.0, log_2_factorials[steps] - log_2_factorials[w_step] - log_2_factorials[h_step] - steps);
}

void solve(int case_id, int w, int h, int l, int u, int r, int d) {
    vector<double> log_2_factorials(w + h + 2, 0.0);
    for(int i = 2; i <= w + h; i++) {
        log_2_factorials[i] = log_2_factorials[i - 1] + log2(i);
    }
    double ans = 0.0;
    // left down
    for(int i = d + 1, j = l - 1; i <= h && j >= 1 ; i += 1, j -= 1) {
        if(i == h) {
            for(int k = 1; k <= j; k++) {
                ans += 0.5 * cal(log_2_factorials, k - 1, i - 2);
            }
        } else {
            ans += cal(log_2_factorials, j - 1, i - 1);
        }
    }
    // right up
    for(int i = u - 1, j = r + 1; i >= 1 && j <= w; i -= 1, j += 1) {
        if(j == w) {
            for(int k = 1; k <= i; k++) {
                ans += 0.5 * cal(log_2_factorials, j - 2, k - 1);
            }
        } else {
            ans += cal(log_2_factorials, j - 1, i - 1);
        }
    }
    cout << "Case #" << case_id << ": " << ans << endl;
}

int main() {
    int t = 0;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int w, h, l, u, r, d;
        cin >> w >> h >> l >> u >> r >> d;
        solve(i, w, h, l, u, r, d);
    }
    return 0;
}


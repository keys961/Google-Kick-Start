#include <iostream>
#include <vector>

using namespace std;

void solve(int case_id, vector<long long>& buses, long long d) {
    long long ans = d;
    for(int i = buses.size() - 1; i >= 0; i--) {
        long long bus = buses[i];
        long long prev = d;
        if(i < buses.size() - 1) {
            prev = buses[i + 1];
        }
        bus = (prev / bus) * bus;
        buses[i] = bus;
        ans = min(ans, bus);
    }
    cout << "Case #" << case_id << ": " << ans << endl;
}

int main() {
    int t = 0;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int n;
        long long d;
        cin >> n >> d;
        vector<long long> buses(n, 0);
        for(int j = 0; j < n; j++) {
            cin >> buses[j];
        }
        solve(i, buses, d);
    }
    return 0;
}

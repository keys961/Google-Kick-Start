#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[]) {
    int t = 0;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int n, b;
        cin >> n >> b;
        int houses[n];
        for (int j = 0; j < n; j++) {
            cin >> houses[j];
        }
        sort(houses, houses + n);
        int cnt = 0;
        for(int j = 0; j < n && b - houses[j] >= 0; j++) {
            b -= houses[j];
            cnt += 1;
        }
        cout << "Case #" << i << ": " << cnt << endl;
    }
}


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct person {
    int amount;
    int index;
    person(int amount, int index): amount(amount), index(index) {}
};

bool operator< (person a, person b) {
    if (a.amount == b.amount) {
        return a.index < b.index;
    }
    return a.amount < b.amount;
}

void solve(int case_id, vector<person>& q) {
    // just need sort
    // first compare withdraw count
    // second the order in the original queue
    sort(q.begin(), q.end());
    cout << "Case #" << case_id << ":";
    for(auto n : q) {
        cout << " " << n.index + 1;
    }
    cout << endl;
}

int main() {
    int t = 0;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int n, x;
        cin >> n >> x;
        vector<person> q;
        for(int j = 0; j < n; j++) {
            int a;
            cin >> a;
            int amount = a / x;
            if(a % x > 0) {
                amount += 1;
            }
            q.emplace_back(amount, j);
        }
        solve(i, q);
    }
    return 0;
}


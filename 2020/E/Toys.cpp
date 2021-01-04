#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct toy {
    int e, r;
    toy(int e, int r): e(e), r(r) {}
};

bool operator< (toy a, toy b) {
    return a.e + a.r < b.e + b.r;
}

int can_loop(vector<toy>& toys) {
    priority_queue<toy> pq;
    long long sum = 0;
    for(toy t : toys) {
        pq.push(t);
        sum += t.e;
    }
    int count = 0;
    while (!pq.empty()) {
        toy top = pq.top();
        // if t.e + t.r <= sum(t.e), can continue loop
        if(top.e + top.r <= sum) {
            return count;
        }
        pq.pop();
        count += 1;
        sum -= top.e;
    }
    return -1;
}

void solve(int case_id, vector<toy>& toys) {
    int cnt = can_loop(toys);
    if(cnt >= 0) {
        cout << "Case #" << case_id << ": " << cnt << " INDEFINITELY" << endl;
        return;
    }
    long long sum = 0;
    for(toy t : toys) {
        sum += t.e;
    }
    long long val = sum;
    long long max_val = val;
    long long min_del = 0;
    int del = 0;
    priority_queue<toy> pq;
    for(toy t : toys) {
        if(t.e + t.r <= sum) {
            // pick it twice
            pq.push(t);
            val += t.e;
            if(val > max_val) {
                max_val = val;
                min_del = del;
            }
        } else {
            // remove t
            sum -= t.e;
            val -= t.e;
            del += 1;
            while(!pq.empty()) {
                toy top = pq.top();
                if(top.e + top.r > sum) {
                    // violate
                    val -= top.e * 2;
                    sum -= top.e;
                    del += 1;
                    pq.pop();
                } else {
                    break;
                }
            }
        }
    }
    cout << "Case #" << case_id << ": " << min_del << " " << max_val << endl;
}

int main() {
    int t = 0;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int n;
        cin >> n;
        vector<toy> toys;
        toys.reserve(n);
        for(int j = 0; j < n; j++) {
            toy toy(0, 0);
            cin >> toy.e >> toy.r;
            toys.emplace_back(toy);
        }
        solve(i, toys);
    }
    return 0;
}


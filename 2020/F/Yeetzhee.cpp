#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <map>

using namespace std;

bool cmp(int a, int b) {
    return a > b;
}

bool state_valid(vector<int>& state, vector<int>& group) {
    if(state.size() > group.size()) {
        return false;
    }
    for(int i = 0; i < state.size(); i++) {
        if(state[i] > group[i]) {
            return false;
        }
    }
    return true;
}

double dfs(vector<int>& state, vector<int>& target, int m,
           map<vector<int>, double>& cache) {
    if(state == target) {
        return 0.0;
    }
    if(cache.find(state) != cache.end()) {
        return cache[state];
    }
    int retry = 0;
    double ans = 0.0;
    for(int i = 0; i < state.size(); i++) {
        vector<int> new_state(state);
        new_state[i] += 1;
        sort(new_state.begin(), new_state.end(), cmp);
        if(state_valid(new_state, target)) {
            ans += (1.0 / m) * (1 + dfs(new_state, target, m, cache));
        } else {
            retry += 1;
        }
    }
    if(state.size() < target.size()) {
        vector<int> new_state(state);
        new_state.push_back(1);
        ans += (1.0 - state.size() * 1.0 / m) * (1 + dfs(new_state, target, m, cache));
    } else {
        retry += m - state.size();
    }
    double retry_pos = retry * 1.0 / m;
    ans = (ans + retry_pos) / (1.0 - retry_pos);
    cache[state] = ans;
    return ans;
}

void solve(int case_id, int m, vector<int>& groups) {
    vector<int> state;
    map<vector<int>, double> cache;
    double ans = dfs(state, groups, m, cache);
    printf("Case #%d: %.6f\n", case_id, ans);
}

int main() {
    int t = 0;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int n, m, k;
        cin >> n >> m >> k; // n dice, from 1~m, k groups
        vector<int> groups(k);
        for(int j = 0; j < k; j++) {
            cin >> groups[j];
        }
        sort(groups.begin(), groups.end(), cmp);
        solve(i, m, groups);
    }
    return 0;
}


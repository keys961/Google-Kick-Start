#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

bool valid(int r, int p, vector<vector<bool>>& constructions, vector<vector<bool>>& visited) {
    return !visited[r][p] && !constructions[r][p];
}

void next_rooms(int r, int p,
                vector<vector<bool>>& constructions, vector<vector<bool>>& visited,
                vector<pair<int, int>>& ret) {
    ret.clear();
    int x = visited.size() - 1;
    int y = 2 * r - 1;
    // up
    if(r > 0 && p % 2 == 0) {
        if(valid(r - 1, p - 1, constructions, visited)) {
            ret.emplace_back(r - 1, p - 1);
        }
    }
    // left
    if(p > 1) {
        if(valid(r, p - 1, constructions, visited)) {
            ret.emplace_back(r, p - 1);
        }
    }
    // right
    if(p < y) {
        if(valid(r, p + 1, constructions, visited)) {
            ret.emplace_back(r, p + 1);
        }
    }
    // down
    if(r < x && p % 2 != 0) {
        if(valid(r + 1, p + 1, constructions, visited)) {
            ret.emplace_back(r + 1, p + 1);
        }
    }
}

// a is first
int dfs(int r_a, int p_a, int r_b, int p_b,
        int count_a, int count_b,
        bool a_over, bool b_over,
        vector<vector<bool>>& constructions, vector<vector<bool>>& visited) {
    if(a_over && b_over) {
        return count_a - count_b;
    }
    vector<pair<int, int>> nexts;
    next_rooms(r_a, p_a, constructions, visited, nexts);
    if(nexts.empty()) {
        a_over = true;
        return -dfs(r_b, p_b, r_a, p_a, count_b, count_a, b_over, a_over, constructions, visited);
    }
    int ret = -100;
    for(auto& next : nexts) {
        visited[next.first][next.second] = true;
        ret = max(ret,  -dfs(r_b, p_b, next.first, next.second, count_b, count_a + 1, b_over, a_over, constructions, visited));
        visited[next.first][next.second] = false;
    }
    return ret;
}

void solve(int case_id, int s, int r_a, int p_a, int r_b, int p_b, vector<vector<bool>>& constructions) {
    vector<vector<bool>> visited(s + 1, vector<bool>(2 * s));
    visited[r_a][p_a] = true;
    visited[r_b][p_b] = true;
    int ans = dfs(r_a, p_a, r_b, p_b, 1, 1, false, false, constructions, visited);
    cout << "Case #" << case_id << ": " << ans << endl;
}

int main() {
    int t = 0;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int s, r_a, p_a, r_b, p_b, c;
        cin >> s >> r_a >> p_a >> r_b >> p_b >> c;
        vector<vector<bool>> constructions(s + 1, vector<bool>(2 * s));
        for(int j = 0; j < c; j++) {
            int r, p;
            cin >> r >> p;
            constructions[r][p] = true;
        }
        solve(i, s, r_a, p_a, r_b, p_b, constructions);
    }
    return 0;
}


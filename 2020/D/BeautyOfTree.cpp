#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

void dfs(vector<vector<int>>& tree,
         vector<int>& expectations,
         int node, vector<int>& path,
         int jump) {
    for(int child : tree[node]) {
        path.push_back(child);
        dfs(tree, expectations, child, path, jump);
        path.pop_back();
    }
    expectations[node] += 1; // paint started from node
    if(path.size() > jump) {
        expectations[path[path.size() - 1 - jump]] += expectations[node]; // paint backward according the jump
    }
}

void get_expectation(vector<vector<int>>& tree, vector<int>& expectations, int jump) {
    vector<int> path;
    path.push_back(1);
    dfs(tree, expectations, 1, path, jump);
}

void solve(int case_id, vector<vector<int>>& tree, int n, int a, int b) {
    vector<int> exp_a(n + 1, 0);
    vector<int> exp_b(n + 1, 0);
    get_expectation(tree, exp_a, a);
    get_expectation(tree, exp_b, b);

    double ans = 0.0;
    for(int i = 1; i <= n; i++) {
        int count_a = exp_a[i];
        int count_b = exp_b[i];
        double pa = count_a * 1.0 / n;
        double pb = count_b * 1.0 / n;
        ans += (pa + pb - pa * pb);
    }
    printf("Case #%d: %.8lf\n", case_id, ans);
}

int main() {
    int t = 0;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int n, a, b;
        cin >> n >> a >> b;
        vector<vector<int>> tree(n + 1, vector<int>());
        for(int node = 2; node <= n; node += 1) {
            int p;
            cin >> p;
            tree[p].push_back(node);
        }
        solve(i, tree, n, a, b);
    }
    return 0;
}


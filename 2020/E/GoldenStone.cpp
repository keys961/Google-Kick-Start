#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
typedef long long ll;
const ll INF = 1e12;

class Solution {
    int n, m, s, r;

    int hash(int si, int ni) const { return si * (n + 1) + ni; };

public:
    void solve(int case_num) {
        printf("Case #%d: ", case_num);
        cin >> n >> m >> s >> r;
        vector<vector<int>> adj(n + 1), needed_by_recipe(s + 1);
        vector<vector<ll>> stone_cost(s + 1, vector<ll>(n + 1, INF)),
                recipe_cost(r, vector<ll>(n + 1));
        vector<vector<int>> ingredients_got(r, vector<int>(n + 1));
        vector<int> ingredients_need(r), product(r);
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].emplace_back(v);
            adj[v].emplace_back(u);
        }

        for (int city = 1; city <= n; ++city) {
            int stone_num;
            cin >> stone_num;
            for (int j = 0; j < stone_num; ++j) {
                int stone;
                cin >> stone;
                stone_cost[stone][city] = 0;
                pq.push({0, hash(stone, city)});
            }
        }

        for (int i = 0; i < r; ++i) {
            cin >> ingredients_need[i];
            for (int j = 0; j < ingredients_need[i]; ++j) {
                int ingredient;
                cin >> ingredient;
                needed_by_recipe[ingredient].emplace_back(i);
            }
            cin >> product[i];
        }

        while (!pq.empty()) {
            auto top = pq.top();
            pq.pop();
            ll c = top.first;
            int u = top.second;
            int stone = u / (n + 1), city = u % (n + 1);
            if (c != stone_cost[stone][city])
                continue;
            for (int recipe : needed_by_recipe[stone]) {
                ingredients_got[recipe][city]++;
                ll nc = recipe_cost[recipe][city] += c;
                if (ingredients_got[recipe][city] == ingredients_need[recipe]) {
                    if (nc < stone_cost[product[recipe]][city]) {
                        stone_cost[product[recipe]][city] = nc;
                        pq.push({nc, hash(product[recipe], city)});
                    }
                }
            }
            for (int nxt : adj[city]) {
                if (c + 1 < stone_cost[stone][nxt]) {
                    stone_cost[stone][nxt] = c + 1;
                    pq.push({c + 1, hash(stone, nxt)});
                }
            }
        }
        ll ans = *min_element(stone_cost[1].begin(), stone_cost[1].end());
        printf("%lld\n", ans == INF ? -1 : ans);
    }
};

int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        Solution solution = Solution();
        solution.solve(i);
    }
}


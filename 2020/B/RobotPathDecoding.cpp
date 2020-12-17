#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>

using namespace std;

int bound = 1000000000;

long long mod(long long a, long long b) {
    long long ret = a % b;
    return ret >= 0 ? ret : ret + b;
}

pair<long long, long long> solve(string& route, unordered_map<int, int>& bracket_table, int start, int end) {
    pair<long long, long long> ans(0, 0);
    int coefficient = 1;
    bool coefficient_context = false;
    for (int i = start; i <= end; ) {
        char c = route[i];
        if(c == 'E') {
            ans.first = mod(ans.first + 1, bound);
            i += 1;
            coefficient = 1;
            coefficient_context = false;
        } else if(c == 'W') {
            ans.first = mod(ans.first - 1, bound);
            i += 1;
            coefficient = 1;
            coefficient_context = false;
        } else if(c == 'S') {
            ans.second = mod(ans.second + 1, bound);
            i += 1;
            coefficient = 1;
            coefficient_context = false;
        } else if(c == 'N') {
            ans.second = mod(ans.second - 1, bound);
            i += 1;
            coefficient = 1;
            coefficient_context = false;
        } else {
            if(c >= '0' && c <= '9') {
                if(!coefficient_context) {
                    coefficient_context = true;
                    coefficient = c - '0';
                } else {
                    coefficient = coefficient * 10 + c - '0';
                }
                i += 1;
            } else {
                if(c == '(') {
                    int right = bracket_table[i];
                    pair<long long, long long> sub_ans = solve(route, bracket_table, i + 1, right - 1);
                    ans.first = mod(ans.first + coefficient * sub_ans.first, bound);
                    ans.second = mod(ans.second + coefficient * sub_ans.second, bound);
                    i = right + 1;
                }
                coefficient = 1;
                coefficient_context = false;
            }
        }
    }
    return ans;
}

void solve(int case_id, string& route) {
    unordered_map<int, int> bracket_table;
    stack<int> stack;
    for(int i = 0; i < route.size(); i++) {
        if(route[i] == '(') {
            stack.push(i);
        } else if(route[i] == ')') {
            int popped = stack.top();
            stack.pop();
            bracket_table[popped] = i;
        }
    }
    pair<long long, long long> ans = solve(route, bracket_table, 0, route.size() - 1);
    long long x = ans.first + 1;
    long long y = ans.second + 1;
    cout << "Case #" << case_id << ": " << x << " " << y << endl;
}

int main() {
    int t = 0;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        string route;
        cin >> route;
        solve(i, route);
    }
    return 0;
}


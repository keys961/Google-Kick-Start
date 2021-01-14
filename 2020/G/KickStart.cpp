#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <map>

using namespace std;

void solve(int case_id, string& s) {
    string kick = "KICK";
    string start = "START";
    int kick_cnt = 0;
    int ans = 0;

    int i = 0;
    while(i < s.length()) {
        char c = s[i];
        if(c == 'K') {
            int j = 0;
            for(; j + i < s.length() && j < 4; j++) {
                if(s[j + i] != kick[j]) {
                    break;
                }
            }
            if(j == 4) {
                kick_cnt += 1;
                i += j - 1;
            } else {
                i += j;
            }

        } else if (c == 'S') {
            int j = 0;
            for(; j + i < s.length() && j < 5; j++) {
                if(s[j + i] != start[j]) {
                    break;
                }
            }
            if(j == 5) {
                ans += kick_cnt;
            }
            i += j;
        } else {
            i += 1;
        }
    }
    cout << "Case #" << case_id << ": " << ans << endl;
}

int main() {
    int t = 0;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        string s;
        cin >> s;
        solve(i, s);
    }
    return 0;
}


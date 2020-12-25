#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool check_consecutive(vector<string>& rec,
                       vector<bool>& visited, vector<vector<int>>& min_indices, vector<vector<int>>& max_indices) {
    for(int i = 0; i < 26; i++) {
        char ch = 'A' + i;
        if(visited[i]) {
            for(int col = 0; col < min_indices[i].size(); col++) {
                if(min_indices[i][col] >= 0) {
                    for (int row = rec.size() - max_indices[i][col] - 1;
                         row <= rec.size() - min_indices[i][col] - 1;
                         row++) {
                        if(rec[row][col] != ch) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

int find(vector<bool>& visited, vector<vector<int>>& min_indices, vector<vector<int>>& max_indices) {
    for(int i = 0; i < 26; i++) {
        if(visited[i]) {
            bool valid = true;
            for(int col = 0; col < min_indices[i].size(); col++) {
                if(min_indices[i][col] > 0) {
                    valid = false;
                    break;
                }
            }
            if(valid) {
                visited[i] = false;
                for(int j = 0; j < 26; j++) {
                    if(visited[j]) {
                        for(int col = 0; col < min_indices[j].size(); col++) {
                            if(max_indices[i][col] >= 0 && max_indices[i][col] + 1 == min_indices[j][col]) {
                                min_indices[j][col] = 0;
                            }
                        }
                    }
                }
                return i;
            }
        }
    }
    return -1;
}

void solve(int case_id, vector<string>& rec,
           vector<bool>& visited, vector<vector<int>>& min_indices, vector<vector<int>>& max_indices) {
    if(!check_consecutive(rec, visited, min_indices, max_indices)) {
        cout << "Case #" << case_id << ": " << -1 << endl;
        return;
    }
    string ans;
    int n = 0;
    for(int i = 0; i < 26; i++) {
        if(visited[i]) {
            n += 1;
        }
    }
    for(int i = 0; i < n; i++) {
        int c = find(visited, min_indices, max_indices);
        if(c < 0) {
            cout << "Case #" << case_id << ": " << -1 << endl;
            return;
        }
        ans.push_back(c + 'A');
    }
    cout << "Case #" << case_id << ": " << ans << endl;
}


int main() {
    int t = 0;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int r, c;
        cin >> r >> c;
        vector<string> rec(r, "");
        vector<vector<int>> min_indices(26, vector<int>(c, -1));
        vector<vector<int>> max_indices(26, vector<int>(c, -1));
        vector<bool> visited(26, false);
        for(int j = 0; j < r; j++) {
            cin >> rec[j];
            for(int k = 0; k < c; k++) {
                char ch = rec[j][k];
                visited[ch - 'A'] = true;
                int row = r - j - 1;
                if(max_indices[ch - 'A'][k] == -1) {
                    max_indices[ch - 'A'][k] = row;
                }
                min_indices[ch - 'A'][k] = row;
            }
        }
        solve(i, rec, visited, min_indices, max_indices);
    }
    return 0;
}


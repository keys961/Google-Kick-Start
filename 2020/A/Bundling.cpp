#include <iostream>
#include <queue>
#include <cstdlib>
#include <string>

using namespace std;

struct TrieNode {
    int cnt;
    TrieNode* child[26];
};

struct Trie {
    TrieNode *root;
    int bundle;
};

TrieNode *createNode();
Trie *create(int k);
void insert(Trie *trie, const std::string& s);
void drop(Trie *trie);
int traverse(Trie *trie);

TrieNode *createNode() {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    node->cnt = 0;
    for(int i = 0; i < 26; i++) {
        node->child[i] = nullptr;
    }
    return node;
}

Trie * create(int k) {
    Trie *trie = (Trie *)malloc(sizeof(Trie));
    trie->root = createNode();
    trie->bundle = k;
    return trie;
}

void insert(Trie *trie, const std::string& s) {
    TrieNode *cur = trie->root;
    for (char c : s) {
        if(cur->child[c - 'A'] == nullptr) {
            cur->child[c - 'A'] = createNode();
        }
        cur = cur->child[c - 'A'];
        cur->cnt += 1;
    }
}

int traverse(Trie *trie) {
    int ans = 0;
    std::queue<TrieNode *> q;
    q.push(trie->root);
    while(!q.empty()) {
        TrieNode *node = q.front();
        q.pop();
        // this prefix can contribute to cnt/bundle_size group
        ans += node->cnt / trie->bundle;
        for(TrieNode *child : node->child) {
            if(child != nullptr) {
                q.push(child);
            }
        }
    }
    return ans;
}

void drop(Trie *trie) {
    std::queue<TrieNode *> q;
    q.push(trie->root);
    while(!q.empty()) {
        TrieNode *node = q.front();
        q.pop();
        for(TrieNode *child : node->child) {
            if(child != nullptr) {
                q.push(child);
            }
        }
        free(node);
    }
    free(trie);
}

void solve(int case_id, vector<string>& strs, int k) {
    Trie *trie = create(k);
    for(string& s : strs) {
        insert(trie, s);
    }
    int ans = traverse(trie);
    cout << "Case #" << case_id << ": " << ans << endl;
    drop(trie);
}

int main() {
    int t = 0;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int n, k;
        cin >> n >> k;
        vector<string> strs(n);
        for(int j = 0; j < n; j++) {
            cin >> strs[j];
        }
        solve(i, strs, k);
    }
    return 0;
}


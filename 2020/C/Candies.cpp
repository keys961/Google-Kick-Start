#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

// -------------------------------------------------------

struct SegmentTree {
    int n;
    long long *data;
    long long (*merge)(long long, long long);
};

SegmentTree* create(std::vector<long long>& data, long long (*merge)(long long, long long));
void update(SegmentTree* tree, int index, long long val);
long long query(SegmentTree *tree, int left, int right);
void drop(SegmentTree* tree);

SegmentTree* create(std::vector<long long>& data, long long (*merge)(long long, long long)) {
    auto *tree = (SegmentTree *)malloc(sizeof(SegmentTree));
    int n = data.size();
    tree->n = n;
    tree->data = (long long*)malloc(sizeof(long long) * n * 2);
    tree->merge = merge;
    for(int i = n; i < 2 * n; i++) {
        tree->data[i] = data[i - n];
    }
    for(int i = n - 1; i > 0; i--) {
        tree->data[i] = tree->merge(tree->data[i * 2], tree->data[i * 2 + 1]);
    }
    return tree;
}

void drop(SegmentTree* tree) {
    free(tree->data);
    free(tree);
}

void update(SegmentTree* tree, int index, long long val) {
    index = index + tree->n;
    tree->data[index] = val;
    while(index > 1) {
        index = index / 2;
        tree->data[index] = tree->merge(tree->data[index * 2], tree->data[index * 2 + 1]);
    }
}

long long query(SegmentTree* tree, int left, int right) {
    // left is close, right is open
    left = left + tree->n;
    right = right + tree->n;
    long long ans = 0;
    while(left < right) {
        if(left % 2 != 0) {
            ans = tree->merge(ans, tree->data[left]);
            left = left + 1;
        }
        if(right % 2 != 0) {
            right = right - 1;
            ans = tree->merge(ans, tree->data[right]);
        }
        left /= 2;
        right /= 2;
    }
    return ans;
}

// ------------------------------------------------

long long merge(long long a, long long b) {
    return a + b;
}

void solve(int case_id, vector<int>& arr, int q) {
    char op;
    int a, b;
    vector<long long> f1(arr.size(), 0);
    vector<long long> f2(arr.size(), 0);
    for(int i = 1; i < arr.size(); i++) {
        // In segment tree, no need to calculate prefix sum
        int flag = i % 2 == 0 ? -1 : 1;
        f1[i] = flag * arr[i] * i;
        f2[i] = flag * arr[i];
    }
    SegmentTree *t1 = create(f1, &merge);
    SegmentTree *t2 = create(f2, merge);
    long long ans = 0;
    while(q-- > 0) {
        cin >> op >> a >> b;
        if(op == 'U') {
            // O(logN) update
            int flag = a % 2 == 0 ? -1 : 1;
            long long v1 = flag * b * a;
            long long v2 = flag * b;
            update(t1, a, v1);
            update(t2, a, v2);
        } else {
            int flag = a % 2 == 0 ? -1 : 1;
            // q(x, y) = (-1)^(x-1) * (f1sum[a:b+1] - (x-1)*f2sum[a:b+1])
            ans += flag * (query(t1, a, b + 1) - (a - 1) * query(t2, a, b + 1));
        }
    }
    cout << "Case #" << case_id << ": " << ans << endl;
}

void solve_tle(int case_id, vector<int>& arr, int q) {
    char op;
    int a, b;
    vector<long long> f1(arr.size(), 0);
    vector<long long> f2(arr.size(), 0);
    for(int i = 1; i < arr.size(); i++) {
        // Prefix sum
        int flag = i % 2 == 0 ? -1 : 1;
        f1[i] = f1[i - 1] + flag * arr[i] * i; // (-1)^(i-1) * arr[i] * i
        f2[i] = f2[i - 1] + flag * arr[i]; // (-1)^(i-1) * arr[i]
    }
    long long ans = 0;
    while(q-- > 0) {
        cin >> op >> a >> b;
        if(op == 'U') {
            // TLE for O(N) update
            arr[a] = b;
            for(int i = a; i < arr.size(); i++) {
                int flag = i % 2 == 0 ? -1 : 1;
                f1[i] = f1[i - 1] + flag * arr[i] * i;
                f2[i] = f2[i - 1] + flag * arr[i];
            }
        } else {
             int flag = a % 2 == 0 ? -1 : 1;
             // q(x, y) = (-1)^(x-1) * ((f1[y]-f1[x-1]) - (x-1)(f2[y]-f2[x-1]))
             ans += flag * ((f1[b] - f1[a - 1]) - (a - 1) * (f2[b] - f2[a - 1]));
        }
    }
    cout << "Case #" << case_id << ": " << ans << endl;
}

int main() {
    int t = 0;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        int n, q;
        cin >> n >> q;
        vector<int> arr(n + 1, 0);
        for(int j = 0; j < n; j++) {
            cin >> arr[j + 1];
        }
        solve(i, arr, q);
    }
    return 0;
}


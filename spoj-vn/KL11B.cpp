#include <algorithm>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;

const int N = 500010;

struct node {
    node *left, *right;
    int sum;
} pool[30000000];

node* avail = pool;
node* tree[N];

int type[N], f[N], t[N];
vector<int> fs, ts;

void update(node*& id, int f, int t, int y) {
    if (id == nullptr) id = avail++;
    ++id->sum;
    if (f < t) {
        int m = (f + t) >> 1;
        if (y < m + 1) update(id->left, f, m, y);
        else update(id->right, m + 1, t, y);
    }
}

void update(int x, int y) {
    for (++x; x <= fs.size(); x += x & -x) {
        update(tree[x], 0, ts.size() - 1, y);
    }
}

int query(node* id, int f, int t, int yf, int yt) {
    if (id == nullptr) return 0;
    if (yf <= f && t <= yt) return id->sum;
    int m = (f + t) >> 1;
    if (yt < m + 1) return query(id->left, f, m, yf, yt);
    if (yf > m) return query(id->right, m + 1, t, yf, yt);
    return query(id->left, f, m, yf, yt) + query(id->right, m + 1, t, yf, yt);
}

int query(int x, int yf, int yt) {
    int result = 0;
    for (++x; x; x &= x - 1) {
        result += query(tree[x], 0, ts.size() - 1, yf, yt);
    }
    return result;
}

int query(int xf, int xt, int yf, int yt) {
    return query(xt, yf, yt) - query(xf - 1, yf, yt);
}

int main() {
//    freopen("in", "r", stdin);
//    freopen("out", "w", stdout);
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    int n;
    cin >> n;
    fs.reserve(n + 2);
    ts.reserve(n + 2);
    for (int i = 1; i <= n; ++i) {
        char c;
        cin >> c >> f[i] >> t[i];
        type[i] = (c == '+');
        if (type[i] == 1) {
            fs.push_back(f[i]);
            ts.push_back(t[i]);
        }
    }
    fs.push_back(1);
    ts.push_back(1);
    fs.push_back(1000000000);
    ts.push_back(1000000000);
    sort(fs.begin(), fs.end());
    fs.erase(unique(fs.begin(), fs.end()), fs.end());
    sort(ts.begin(), ts.end());
    ts.erase(unique(ts.begin(), ts.end()), ts.end());
    for (int i = 1; i <= n; ++i) {
        if (type[i] == 1) {
            f[i] = lower_bound(fs.begin(), fs.end(), f[i]) - fs.begin();
            t[i] = lower_bound(ts.begin(), ts.end(), t[i]) - ts.begin();
            update(f[i], t[i]);
        } else {
            int xf = 0, xt = upper_bound(fs.begin(), fs.end(), f[i]) - fs.begin() - 1;
            int yf = lower_bound(ts.begin(), ts.end(), t[i]) - ts.begin(), yt = ts.size() - 1;
            int ans = query(xf, xt, yf, yt);
            cout << ans << '\n';
        }
    }
}

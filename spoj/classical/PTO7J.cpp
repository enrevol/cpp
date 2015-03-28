#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>

const int N = 100010;

struct node {
    node *left, *right;
    int cnt;
} pool[N * 20];

node* avail = pool;
node* root[N << 1];

int a[N], tin[N], tout[N], b[N], c[N];
std::vector<int> vals, adj[N];

node* build(int f, int t) {
    node* r = avail++;
    if (f < t) {
        int m = (f + t) >> 1;
        r->left = build(f, m);
        r->right = build(m + 1, t);
    }
    return r;
}

node* insert(node* x, int f, int t, int p) {
    node* r = avail++;
    r->left = x->left;
    r->right = x->right;
    r->cnt = x->cnt + 1;
    if (f < t) {
        int m = (f + t) >> 1;
        if (p < m + 1) r->left = insert(x->left, f, m, p);
        else r->right = insert(x->right, m + 1, t, p);
    }
    return r;
}

int query(node* xf, node* xt, int f, int t, int k) {
    if (f == t) return f;
    int m = (f + t) >> 1;
    int cnt = xt->left->cnt - xf->left->cnt;
    if (cnt >= k) return query(xf->left, xt->left, f, m, k);
    return query(xf->right, xt->right, m + 1, t, k - cnt);
}

void dfs(int u, int& tn) {
    c[tin[u] = ++tn] = u;
    for (int v : adj[u])
        if (!tin[v])
            dfs(v, tn);
    tout[u] = tn;
//    c[tout[u] = ++tn] = u;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    vals.insert(vals.begin(), a + 1, a + n + 1);
    std::sort(vals.begin(), vals.end());
    for (int i = 1; i <= n; ++i) {
        a[i] = std::lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();
        b[a[i]] = i;
    }
    for (int i = 1; i < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int tn = 0;
    dfs(1, tn);
    root[0] = build(0, vals.size() - 1);
    for (int i = 1; i <= tn; ++i) {
        root[i] = insert(root[i - 1], 0, vals.size() - 1, a[c[i]]);
    }
    int m;
    std::cin >> m;
    while (m--) {
        int x, k;
        std::cin >> x >> k;
        int u = query(root[tin[x] - 1], root[tout[x]], 0, vals.size() - 1, k);
        std::cout << b[u] << '\n';
    }
}
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

const int N = 300010;
const int MOD = 1e9 + 7;

struct node {
    node *left, *right;
    int sum, cnt;
    node();
} pool[N * 20];

node* const NIL = pool;
node* avail = pool + 1;
node* root[N];

node::node() : left(NIL), right(NIL), sum(0), cnt(0) { }

int a[N], f[N], fw[N];

void update(int i, int v) {
    while (i < N) {
        fw[i] += v;
        i += i & -i;
    }
}

int query(int i) {
    int r = 0;
    while (i > 0) {
        r += fw[i];
        i &= i - 1;
    }
    return r;
}

node* insert(node* x, int f, int t, int p, int v) {
    node* r = avail++;
    r->left = x->left;
    r->right = x->right;
    r->sum = (x->sum + v) % MOD;
    r->cnt = x->cnt + 1;
    if (f < t) {
        int m = (f + t) / 2;
        if (p < m + 1) r->left = insert(x->left, f, m, p, v);
        else r->right = insert(x->right, m + 1, t, p, v);
    }
    return r;
}

int query_cnt(node* xf, node* xt, int f, int t, int qf, int qt) {
    if (qf <= f && t <= qt) return xt->cnt - xf->cnt;
    int m = (f + t) / 2;
    if (qt < m + 1) return query_cnt(xf->left, xt->left, f, m, qf, qt);
    if (qf > m) return query_cnt(xf->right, xt->right, m + 1, t, qf, qt);
    return query_cnt(xf->left, xt->left, f, m, qf, qt) + query_cnt(xf->right, xt->right, m + 1, t, qf, qt);
}

long long query_sum(node* xf, node* xt, int f, int t, int qf, int qt) {
    if (qf <= f && t <= qt) return xt->sum - xf->sum;
    int m = (f + t) / 2;
    if (qt < m + 1) return query_sum(xf->left, xt->left, f, m, qf, qt);
    if (qf > m) return query_sum(xf->right, xt->right, m + 1, t, qf, qt);
    return query_sum(xf->left, xt->left, f, m, qf, qt) + query_sum(xf->right, xt->right, m + 1, t, qf, qt);
}

int main() {
//    freopen("in", "r", stdin);
//    freopen("out", "w", stdout);
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    f[0] = 1;
    for (int i = 1; i < N; ++i) {
        f[i] = (long long)f[i - 1] * i % MOD;
    }
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    int pos = 1;
    for (int i = n; i >= 1; --i) {
        int v = query(a[i]);
        pos = (pos + (long long)f[n - i] * v) % MOD;
        update(a[i], 1);
    }
    root[0] = NIL;
    for (int i = 1; i <= n; ++i) {
        root[i] = insert(root[i - 1], 1, n, a[i], f[n - i]);
    }
    cerr << "pos = " << pos << '\n';
    while (m--) {
        int x, y;
        cin >> x >> y;
        long long answer = pos;
        if (a[x] < a[y]) {
            answer -= (long long)f[n - y] * query_cnt(root[y], root[n], 1, n, a[x], a[y]);
            answer += (long long)f[n - x] * query_cnt(root[x], root[n], 1, n, a[x], a[y]);
            answer += query_sum(root[x], root[y - 1], 1, n, a[x], a[y]);
        } else if (a[x] > a[y]) {
            answer += (long long)f[n - y] * query_cnt(root[y], root[n], 1, n, a[y], a[x]);
            answer -= (long long)f[n - x] * query_cnt(root[x], root[n], 1, n, a[y], a[x]);
            answer -= query_sum(root[x], root[y - 1], 1, n, a[y], a[x]);
        }
        answer %= MOD;
        if (answer < 0) answer += MOD;
        cout << answer << '\n';
    }
    cerr << "used = " << avail - pool << '\n';
}

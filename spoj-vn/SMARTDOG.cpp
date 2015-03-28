#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;

const int MAX = 1000;
const int B_MAX = 2 * MAX;
const int T_MAX = 2 * B_MAX;

struct node {
    node *left, *right;
    int v;
    node();
} pool[3000000];

node* const NIL = pool;
node* avail = pool + 1;

node::node() : left(NIL), right(NIL), v(0) { }

node* tree[T_MAX << 2];

int dp[MAX + 1][MAX + 1];

int ux, uy, uv;

void y_update(node*& x, int f, int t) {
    if (x == NIL) x = avail++;
    if (f == t) {
        x->v = max(x->v, uv);
    } else {
        int m = (f + t) >> 1;
        if (uy < m + 1) y_update(x->left, f, m);
        else y_update(x->right, m + 1, t);
        x->v = max(x->left->v, x->right->v);
    }
}

void x_update(int xid, int f, int t) {
    y_update(tree[xid], 0, T_MAX);
    if (f < t) {
        int m = (f + t) >> 1;
        if (ux < m + 1) x_update(xid << 1, f, m);
        else x_update(xid << 1 | 1, m + 1, t);
    }
}

int xff, xtt, yff, ytt;

int y_query(node* x, int f, int t) {
    if (x == NIL) return 0;
    if (yff <= f && t <= ytt) return x->v;
    int m = (f + t) >> 1;
    if (ytt < m + 1) return y_query(x->left, f, m);
    if (yff > m) return y_query(x->right, m + 1, t);
    return max(y_query(x->left, f, m), y_query(x->right, m + 1, t));
}

int x_query(int xid, int f, int t) {
    if (xff <= f && t <= xtt) return y_query(tree[xid], 0, T_MAX);
    int m = (f + t) >> 1;
    if (xtt < m + 1) return x_query(xid << 1, f, m);
    if (xff > m) return x_query(xid << 1 | 1, m + 1, t);
    return max(x_query(xid << 1, f, m), x_query(xid << 1 | 1, m + 1, t));
}

void update(int x, int y, int v) {
    ux = x - y + B_MAX;
    uy = x + y - MAX;
    uv = v;
    x_update(1, 0, T_MAX);
}

int query(int xf, int yf, int xt, int yt) {
    xff = xf - yf + B_MAX;
    yff = xf + yf - MAX;
    xtt = xt - yt + B_MAX;
    ytt = xt + yt - MAX;
    return x_query(1, 0, T_MAX);
}

int main() {
//    freopen("in", "r", stdin);
//    freopen("out", "w", stdout);
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    fill(begin(tree), end(tree), NIL);
    int n, k;
    cin >> n >> k;
    dp[0][0] = 1;
    update(0 + MAX, 0 + MAX, 1);
    int answer = 1;
    for (int i = 1; i <= n; ++i) {
        int x, y, c;
        cin >> x >> y >> c;
        int xx = x + MAX;
        int yy = y + MAX;
        int v = query(xx - k, yy, xx + k, yy);
        if (v > 0 && v + c > dp[x][y]) {
            dp[x][y] = v + c;
            update(xx, yy, dp[x][y]);
            if (v + c > answer) {
                answer = v + c;
            }
        }
    }
    cout << answer - 1;
}

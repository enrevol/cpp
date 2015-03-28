#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>
#include <vector>

const int N = 50010;
const int Q = 100010;

struct node {
    node *left, *right;
    long long sum;
    node();
} pool[N * 50];

node* const NIL = pool;

node::node() : left(NIL), right(NIL) { }

node* avail = pool + 1;
node* root[N];
node* add_root[N];

int n, a[N], last[N + Q];
std::set<int> pos[N + Q];
std::vector<int> vals;

struct query {
    int type, arg1, arg2;
} q[Q];

node* insert(node* x, int f, int t, int p, int v, bool create) {
    node* res = x;
    if (create || x == NIL) {
        res = avail++;
        res->left = x->left;
        res->right = x->right;
    }    
    res->sum = x->sum + v;
    if (f < t) {
        int m = (f + t) >> 1;
        if (p < m + 1) res->left = insert(x->left, f, m, p, v, create);
        else res->right = insert(x->right, m + 1, t, p, v, create);
    }
    return res;
}

long long query(node* x, int f, int t, int p) {
    if (p <= f) return x->sum;
    int m = (f + t) >> 1;
    if (p > m) return query(x->right, m + 1, t, p);
    return query(x->left, f, m, p) + x->right->sum;
}

long long query(int f, int t) {
    long long res = query(root[t], 1, n, f);
    for (int i = t; i; i &= i - 1) {
        res = res + query(add_root[i], 1, n, f);
    }
    return res;
}

void update(int t, int p, int v) {
    for (int i = t; i <= n; i += i & -i) {
        add_root[i] = insert(add_root[i], 1, n, p, v, false);
    }
}

inline
int find(int x) {
    return std::lower_bound(vals.begin(), vals.end(), x) - vals.begin() + 1;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    vals.insert(vals.begin(), a + 1, a + n + 1);
    int m;
    std::cin >> m;
    for (int i = 1; i <= m; ++i) {
        char type;
        std::cin >> type >> q[i].arg1 >> q[i].arg2;
        q[i].type = type == 'Q';
        if (q[i].type == 0) {
            vals.push_back(q[i].arg2);
        }
    }
    std::sort(vals.begin(), vals.end());
    vals.erase(std::unique(vals.begin(), vals.end()), vals.end());
    for (int i = 1; i <= int(vals.size()); ++i) {
        pos[i].insert(0);
        pos[i].insert(n + 1);
    }
    std::fill(root, root + n + 1, NIL);
    std::fill(add_root + 1, add_root + n + 1, NIL);
    for (int i = 1; i <= n; ++i) {
        a[i] = find(a[i]);
        int p = last[a[i]];
        if (p > 0) {
            root[i] = insert(insert(root[i - 1], 1, n, p, -vals[a[i] - 1], true), 1, n, i, vals[a[i] - 1], true);
        } else {
            root[i] = insert(root[i - 1], 1, n, i, vals[a[i] - 1], true);
        }
        last[a[i]] = i;
        pos[a[i]].insert(i);
    }
    for (int i = 1; i <= m; ++i) {
        if (q[i].type == 0) {
            int p = q[i].arg1;
            int v = find(q[i].arg2);
            
            auto old = pos[a[p]].upper_bound(p);
            int old_t = *old;
            int old_f = *(--(--old));
            int old_v = vals[a[p] - 1];            
            pos[a[p]].erase(p);            
            update(p, p, -old_v);
            if (old_f > 0) {
                update(p, old_f, old_v);
            }
            if (old_t <= n) {
                update(old_t, p, old_v);
                if (old_f > 0) {
                    update(old_t, old_f, -old_v);
                }
            }
            
            auto now = pos[a[p] = v].upper_bound(p);
            int now_t = *now;
            int now_f = *(--now);
            int now_v = vals[a[p] - 1];
            pos[a[p]].insert(p);
            update(p, p, now_v);
            if (now_f > 0) {
                update(p, now_f, -now_v);
            }
            if (now_t <= n) {
                update(now_t, p, -now_v);
                if (now_f > 0) {
                    update(now_t, now_f, now_v);
                }
            }
        } else {
            int f = q[i].arg1;
            int t = q[i].arg2;
            long long ans = query(f, t);
            std::cout << ans << '\n';
        }
    }
    std::cerr << avail - pool << '\n';
}
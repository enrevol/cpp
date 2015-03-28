#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

const int N = 100010;

int tree[N << 2][3], lazy[N << 2];

void modify(int id, int v) {
    v = v % 3;
    if (v == 1) {
        int tmp = tree[id][0];
        tree[id][0] = tree[id][2];
        tree[id][2] = tree[id][1];
        tree[id][1] = tmp;
    } else if (v == 2) {
        int tmp = tree[id][0];
        tree[id][0] = tree[id][1];
        tree[id][1] = tree[id][2];
        tree[id][2] = tmp;
    }
    lazy[id] += v;
}

void build(int id, int f, int t) {
    tree[id][0] = t - f + 1;
    if (f < t) {
        int m = (f + t) >> 1;
        build(id << 1, f, m);
        build(id << 1 | 1, m + 1, t);
    }
}

void push(int id, int f, int t) {
    if (lazy[id] && f < t) {
        modify(id << 1, lazy[id]);
        modify(id << 1 | 1, lazy[id]);
        lazy[id] = 0;
    }
}

void update(int id, int f, int t, int qf, int qt) {
    push(id, f, t);
    if (qf <= f && t <= qt) {
        modify(id, 1);
    } else {
        int m = (f + t) >> 1;
        if (qf < m + 1) update(id << 1, f, m, qf, qt);
        if (qt > m) update(id << 1 | 1, m + 1, t, qf, qt);
        tree[id][0] = tree[id << 1][0] + tree[id << 1 | 1][0];
        tree[id][1] = tree[id << 1][1] + tree[id << 1 | 1][1];
        tree[id][2] = tree[id << 1][2] + tree[id << 1 | 1][2];
    }
}

int query(int id, int f, int t, int qf, int qt) {
    if (qt < f || t < qf) return 0;
    push(id, f, t);
    if (qf <= f && t <= qt) return tree[id][0];
    int m = (f + t) >> 1;
    return query(id << 1, f, m, qf, qt) + query(id << 1 | 1, m + 1, t, qf, qt);
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    int n, m;
    std::cin >> n >> m;
    build(1, 1, n);
    while (m--) {
        int type, f, t;
        std::cin >> type >> f >> t;
        ++f, ++t;
        if (type == 0) {
            update(1, 1, n, f, t);
        } else {
            int res = query(1, 1, n, f, t);
            std::cout << res << '\n';
        }
    }
}
#include <algorithm>
#include <iostream>
#include <vector>
 
const int N = 250000;
const int M = 10000;
 
int a[N], pos[M], val[M], tarr[2][N];
std::vector<int> tree[1 << 19 | 1], fw[1 << 19 | 1], vals[N];
 
void update(int id, int p, int v) {
    int sz = fw[id].size();
    while (p < sz) {
        fw[id][p] += v;
        p += p & -p;
    }
}
 
int query(int id, int p) {
    int res = 0;
    while (p > 0) {
        res += fw[id][p];
        p &= p - 1;
    }
    return res;
}
 
void build(int x, int f, int t, int d) {
    if (f == t) {
        tree[x].swap(vals[f]);
        tree[x].push_back(a[f]);
        std::sort(tree[x].begin(), tree[x].end());
        tree[x].erase(std::unique(tree[x].begin(), tree[x].end()), tree[x].end());        
        tarr[d][f] = a[f];
    } else {
        int m = (f + t) >> 1;
        build(x << 1, f, m, d ^ 1);
        build(x << 1 | 1, m + 1, t, d ^ 1);
        tree[x].reserve(tree[x << 1].size() + tree[x << 1 | 1].size());
        std::set_union(tree[x << 1].begin(), tree[x << 1].end(), tree[x << 1 | 1].begin(), tree[x << 1 | 1].end(), std::back_inserter(tree[x]));
        std::merge(tarr[d ^ 1] + f, tarr[d ^ 1] + m + 1, tarr[d ^ 1] + m + 1, tarr[d ^ 1] + t + 1, tarr[d] + f);
    }
    fw[x].resize(tree[x].size() + 1);
    for (int i = f, j = 0; i <= t; ++i) {
        while (tree[x][j] < tarr[d][i]) ++j;
        update(x, j + 1, 1);
    }
}
 
void update(int x, int f, int t, int p, int v, int k) {
    int z = std::lower_bound(tree[x].begin(), tree[x].end(), v) - tree[x].begin();
    update(x, z + 1, k);
    if (f < t) {
        int m = (f + t) >> 1;
        if (p < m + 1) update(x << 1, f, m, p, v, k);
        else update(x << 1 | 1, m + 1, t, p, v, k);
    }
}
 
int query(int x, int f, int t, int qf, int qt, int v) {
    if (qt < f || t < qf) return 0;
    if (qf <= f && t <= qt) {
        int z = std::upper_bound(tree[x].begin(), tree[x].end(), v) - tree[x].begin();
        return query(x, z);
    }
    int m = (f + t) >> 1;
    return query(x << 1, f, m, qf, qt, v) + query(x << 1 | 1, m + 1, t, qf, qt, v);
}
 
int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    tree[0].insert(tree[0].begin(), a, a + n);
    std::sort(tree[0].begin(), tree[0].end());
    tree[0].erase(std::unique(tree[0].begin(), tree[0].end()), tree[0].end());
    fw[0].resize(tree[0].size() + 1);
    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        std::cin >> pos[i] >> val[i];
        --pos[i];
        vals[pos[i]].push_back(val[i]);
    }
    build(1, 0, n - 1, 0);
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        int p = std::lower_bound(tree[0].begin(), tree[0].end(), a[i]) - tree[0].begin();
        int cnt = query(0, p + 1);
        ans += i - cnt;
        update(0, p + 1, 1);
    }
    std::cerr << "cnt = " << ans << '\n';
    for (int i = 0; i < m; ++i) {
        int p = pos[i];
        int v = val[i];
        int cnt1 = query(1, 0, n - 1, 0, p - 1, a[p]);
        int cnt2 = query(1, 0, n - 1, p + 1, n - 1, a[p] - 1);
        int cnt3 = query(1, 0, n - 1, 0, p - 1, v);
        int cnt4 = query(1, 0, n - 1, p + 1, n - 1, v - 1);
        ans = ans - (p - cnt1) - cnt2 + (p - cnt3) + cnt4;
        update(1, 0, n - 1, p, a[p], -1);
        update(1, 0, n - 1, p, a[p] = v, 1);
        std::cout << ans << '\n';
    }
} 
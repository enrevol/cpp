#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>
#include <vector>

const int N = 100010;

struct query {
    int type, arg1, arg2;
} q[N];

int n, a[N];
std::set<int> pos[N + N];
std::vector<int> vals;

inline
void compress(std::vector<int>& vect) {
    std::sort(vect.begin(), vect.end());
    vect.erase(std::unique(vect.begin(), vect.end()), vect.end());
}

class range_tree {
    class fenwick_tree {
        int size;
        std::vector<long long> data;
        
        inline
        void update(int p, int v) {
            while (p <= size) {
                data[p] = data[p] + v;
                p += p & -p;
            }
        }
        
    public:
        void resize(int n) {
            size = n;
            data.resize(n + 1);
        }
        
        inline
        long long query(int p) const {
            long long r = 0;
            while (p > 0) {
                r = r + data[p];
                p &= p - 1;
            }
            return r;
        }
        
        inline
        void update(int f, int t, int v) {
            update(f, v);
            update(t + 1, -v);
        }
    } fw[N << 2];
    
    std::vector<int> vals[N << 2 | 1];
    
    void build(int id, int f, int t) {
        if (f == t) {
            compress(vals[id]);
        } else {
            int m = (f + t) >> 1;
            build(id << 1, f, m);
            build(id << 1 | 1, m + 1, t);
            vals[id].reserve(vals[id << 1].size() + vals[id << 1 | 1].size());
            std::set_union(vals[id << 1].begin(), vals[id << 1].end(), vals[id << 1 | 1].begin(), vals[id << 1 | 1].end(), std::back_inserter(vals[id]));
        }
        fw[id].resize(vals[id].size());
    }
    
    void insert(int id, int f, int t, int x, int y) {
        if (f == t) {
            vals[id].push_back(y);
        } else {
            int m = (f + t) >> 1;
            if (x < m + 1) insert(id << 1, f, m, x, y);
            else insert(id << 1 | 1, m + 1, t, x, y);
        }
    }
    
    void update(int id, int f, int t, int xf, int xt, int yf, int yt, int v) {
        if (xf <= f && t <= xt) {
            int pf = std::lower_bound(vals[id].begin(), vals[id].end(), yf) - vals[id].begin() + 1;
            int pt = std::upper_bound(vals[id].begin(), vals[id].end(), yt) - vals[id].begin();
            fw[id].update(pf, pt, v);
        } else {
            int m = (f + t) >> 1;
            if (xf < m + 1) update(id << 1, f, m, xf, xt, yf, yt, v);
            if (xt > m) update(id << 1 | 1, m + 1, t, xf, xt, yf, yt, v);
        }
    }
    
public:
    void build() {
        build(1, 1, n);
    }
    
    inline    
    void insert(int x, int y) {
        insert(1, 1, n, x, y);
    }
    
    inline
    void update(int xf, int xt, int yf, int yt, int v) {
        update(1, 1, n, xf, xt, yf, yt, v);
    }
    
    long long query(int x, int y) const {
        long long res = 0;
        int id = 1, f = 1, t = n;
        for (;;) {
            int p = std::lower_bound(vals[id].begin(), vals[id].end(), y) - vals[id].begin() + 1;
            res = res + fw[id].query(p);
            if (f == t) break;
            int m = (f + t) >> 1;
            id <<= 1;
            if (x < m + 1) {
                t = m;
            } else {
                ++id;
                f = m + 1;
            }
        }
        return res;
    }
} tree;

inline
int find(int x) {
    return std::lower_bound(vals.begin(), vals.end(), x) - vals.begin() + 1;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
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
        } else {
            tree.insert(q[i].arg1, q[i].arg2);
        }
    }
    tree.build();
    compress(vals);
    for (int i = 1; i <= int(vals.size()); ++i) {
        pos[i].insert(0);
        pos[i].insert(n + 1);
    }
    for (int i = 1; i <= n; ++i) {
        a[i] = find(a[i]);
        auto p = pos[a[i]].upper_bound(i);
        int t = *p;
        int f = *(--p);
        tree.update(f + 1, i, i, t - 1, vals[a[i] - 1]);
        pos[a[i]].insert(i);
    }
    for (int i = 1; i <= m; ++i) {
        if (q[i].type == 0) {
            int p = q[i].arg1;
            int v = find(q[i].arg2);
            auto old = pos[a[p]].upper_bound(p);
            int old_t = *old;
            int old_f = *(--(--old));
            pos[a[p]].erase(p);
            tree.update(old_f + 1, p, p, old_t - 1, -vals[a[p] - 1]);
            auto now = pos[a[p] = v].upper_bound(p);
            int now_t = *now;
            int now_f = *(--now);
            pos[a[p]].insert(p);
            tree.update(now_f + 1, p, p, now_t - 1, vals[a[p] - 1]);
        } else {
            long long ans = tree.query(q[i].arg1, q[i].arg2);
            std::cout << ans << '\n';
        }
    }
}
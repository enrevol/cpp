#include <algorithm>
#include <iostream>
#include <vector>

const int N = 123456;
const int SZ = 320;

struct query {
    int f, t, id;
    
    friend
    bool operator<(const query& a, const query& b) {
        if (a.f / SZ != b.f / SZ)
            return a.f < b.f;
        return a.t < b.t;
    }
} q[N];

int r, a[N], z[N], c[N], ans[N];

inline
void add(int x) {
    --z[c[x]++];
    ++z[c[x]];
    if (r < c[x]) r = c[x];
}

inline
void rem(int x) {
    --z[c[x]];
    ++z[--c[x]];
    if (z[r] == 0) --r;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 1; i <= m; ++i) {
        std::cin >> q[i].f >> q[i].t;
        q[i].id = i;
    }
    std::sort(q + 1, q + m + 1);
    int f = 1, t = 0;
    z[0] = n;
    for (int i = 1; i <= m; ++i) {
        int qf = q[i].f + 1;
        int qt = q[i].t + 1;
        while (t < qt) add(a[++t]);
        while (t > qt) rem(a[t--]);
        while (f < qf) rem(a[f++]);
        while (f > qf) add(a[--f]);
//        std::cerr << "[" << qf << ".." << qt << "] = " << r << '\n';
        ans[q[i].id] = r;
    }
    for (int i = 1; i <= m; ++i) {
        std::cout << ans[i] << '\n';
    }
}
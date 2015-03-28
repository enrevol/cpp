#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

const int N = 123456;

struct edge {
    int u, v, c;
} e[N];

int c[N], p[N];

int main() {
//    freopen("input.txt", "r", stdin);
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    int tt;
    std::cin >> tt;
    while (tt--) {
        int n;
        std::cin >> n;
        for (int i = 1; i < n; ++i) {
            std::cin >> e[i].u >> e[i].v >> e[i].c;
        }
        std::sort(e + 1, e + n, [] (const edge& a, const edge& b) { return a.c > b.c; } );
        for (int i = 1; i <= n; ++i) {
            p[i] = i;
            c[i] = 1;
        }            
        std::function<int(int)> find = [&find] (int u) {
            if (p[u] != u)
                p[u] = find(p[u]);
            return p[u];
        };
        long long ans = 0;
        for (int i = 1; i < n; ++i) {
            int u = e[i].u;
            int v = e[i].v;
            u = find(u);
            v = find(v);
            ans = ans + 2LL * e[i].c * c[u] * c[v];
            if (c[u] > c[v]) {
                std::swap(u, v);
            }
            p[u] = v;
            c[v] = c[v] + c[u];
        }
        std::cout << ans << '\n';
    }
}
#include <algorithm>
#include <iostream>
#include <vector>

const int N_MAX = 100000;

int n, k, ans, a[N_MAX + 1];
std::vector<int> adj[N_MAX + 1];

void dfs(int u, int p, int l, int x, int y) {
    if (l > 1 && y - x >= k) {
        ++ans;
//        std::cerr << "  u = " << u << '\n';
    }
    for (auto v : adj[u])
        if (v != p) {
            dfs(v, u, l + 1, std::min(x, a[v]), std::max(y, a[v]));
        }
}

int main() {
//    freopen("input.txt", "r", stdin);
    std::cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 1; i < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) {
//        std::cerr << "r = " << i << '\n';
        dfs(i, 0, 1, a[i], a[i]);
    }
    std::cout << ans / 2;
}
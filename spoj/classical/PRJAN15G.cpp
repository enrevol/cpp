#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

const int N = 123456;
const int M = 234567;

struct edge {
    int u, v;
    bool bridge;
    
    inline
    int get(int x) const {
        return u ^ v ^ x;
    }
} e[M];

std::vector<int> adj[N], t_adj[N];
int tin[N], low[N], cnt[N], depth[N], ancestor[17][N];

void dfs(int u, int p, int& t) {
    depth[u] = depth[p] + 1;
    ancestor[0][u] = p;
    tin[u] = low[u] = ++t;
    for (auto i : adj[u]) {
        int v = e[i].get(u);
        if (v != p) {
            if (tin[v] > 0) {
                low[u] = std::min(low[u], tin[v]);
            } else {
                t_adj[u].push_back(i);
                dfs(v, u, t);
                low[u] = std::min(low[u], low[v]);
            }
        }
    }
}

void dfs_cnt(int u) {
    for (int i : t_adj[u]) {
        int v = e[i].get(u);
        cnt[v] = cnt[u] + e[i].bridge;
        dfs_cnt(v);
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        std::swap(u, v);
    }
    for (int i = 16; i >= 0; --i)
        if (depth[u] - (1 << i) >= depth[v])
            u = ancestor[i][u];
    if (u == v) return u;
    for (int i = 16; i >= 0; --i)
        if (ancestor[i][u] != ancestor[i][v]) {
            u = ancestor[i][u];
            v = ancestor[i][v];
        }
    return ancestor[0][u];
}

int main() {
//    freopen("input.txt", "r", stdin);
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);
    int tt;
    std::cin >> tt;
    for (int tn = 1; tn <= tt; ++tn) {
        int n, m;
        std::cin >> n >> m;
        for (int i = 1; i <= n; ++i) {
            adj[i].clear();
            t_adj[i].clear();
        }
        for (int i = 1; i <= m; ++i) {
            int u, v;
            std::cin >> u >> v;
            e[i] = { u, v, false };
            adj[u].push_back(i);
            adj[v].push_back(i);
        }
        std::memset(ancestor, 0, sizeof(ancestor));
        std::memset(tin, 0, sizeof(tin));
        std::memset(low, 0, sizeof(low));
        int t = 0;
        dfs(1, 0, t);
        for (int i = 1; 1 << i <= n; ++i)
            for (int u = 1; u <= n; ++u)
                ancestor[i][u] = ancestor[i - 1][ancestor[i - 1][u]];
        for (int u = 1; u <= n; ++u)
            for (int i : t_adj[u]) {
                int v = e[i].get(u);
                if (low[v] > tin[u]) {
                    e[i].bridge = true;
                }
            }
        std::memset(cnt, 0, sizeof(cnt));
        dfs_cnt(1);
        int q;
        std::cin >> q;
        std::cout << "Case " << tn << ":\n";
        while (q--) {
            int u, v;
            std::cin >> u >> v;
            int x = lca(u, v);
            int r = cnt[v] + cnt[u] - (cnt[x] << 1);
            std::cout << r << '\n';
        }
    }
}
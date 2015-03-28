#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

const int N = 23456;

struct edge {
    int u, v;
    bool mark;
    
    inline
    int get(int x) const {
        assert(x == u || x == v);
        return u ^ v ^ x;
    }
} e[N];

bool mark[N + 1];
int sub[N + 1], cnt[N + 1];
std::vector<int> adj[N + 1];

void dfs(int u, int p) {
    sub[u] = 1;
    cnt[u] = 0;
    for (auto i : adj[u]) {
        int v = e[i].get(u);
        if (v != p) {
            dfs(v, u);
            sub[u] += sub[v];
            cnt[u] += cnt[v] + e[i].mark;
        }
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    int tt;
    std::cin >> tt;
    while (tt--) {
        int n, k;
        std::cin >> n >> k;
        for (int i = n; i >= 1; --i) {
            adj[i].clear();
        }
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            std::cin >> u >> v;
            e[i] = { u, v, false };
            adj[u].push_back(i);
            adj[v].push_back(i);
        }
        long long ans = 0;
        assert(k > 0);
        std::fill(mark + 1, mark + n + 1, false);
        for (int i = 0; i < k; ++i) {
            int id;
            std::cin >> id;
            e[id].mark = true;
            mark[e[id].u] = mark[e[id].v] = true;
        }
        int root = 0;
        dfs(1, 0);
        for (int i = 1; i <= n; ++i)
            if (cnt[i] == 0 && mark[i]) {
                root = i;
                break;
            }
        assert(root != 0);
        dfs(root, 0);
        int dest = root;
        bool ok = true;
        while (ok) {                
            int next = 0;
            for (auto i : adj[dest]) {
                int v = e[i].get(dest);
                if (sub[v] < sub[dest])
                    if (cnt[v] > 0 || e[i].mark) {
                        if (next != 0) {
                            ok = false;
                            break;
                        }
                        next = v;
                    }
            }
            if (next == 0) break;
            dest = next;
        }
        if (ok == true) {
            assert(root != dest);
            int z = sub[root];
            for (auto i : adj[root]) {
                int v = e[i].get(root);
                if (cnt[v] > 0 || e[i].mark) {
                    z -= sub[v];
                    break;
                }
            }
            ans = 1LL * z * sub[dest];
        }
        std::cout << ans << '\n';
    }
}
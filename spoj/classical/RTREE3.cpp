#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

const int N = 100010;
const int Q = 200010;
const int INF = 1e9;

bool used[N];
int sub[N], depth[N];
int tadd[N], index[N], d_index[N];
int ans_dist[Q], ans_vert[Q];
std::vector<int> adj[N], queries[N], verts[N], d_vals[N];

class seg_tree {
    int size;
    std::vector<int> tree;
    
    void update(int x, int f, int t, int p, int v) {
        if (f == t) {
            tree[x] = v;
        } else {
            int m = (f + t) >> 1;
            if (p < m + 1) update(x << 1, f, m, p, v);
            else update(x << 1 | 1, m + 1, t, p, v);
            tree[x] = std::max(tree[x << 1], tree[x << 1 | 1]);
        }
    }
    
    int query(int x, int f, int t, int p) const {
        if (t <= p) return tree[x];
        int m = (f + t) >> 1;
        if (p < m + 1) return query(x << 1, f, m, p);
        return std::max(tree[x << 1], query(x << 1 | 1, m + 1, t, p));
    }
    
public:
    inline
    void resize(int n, int v) {
        size = n;
        tree.resize(n << 2 | 1);
        std::fill(tree.begin(), tree.end(), v);
    }
    
    inline
    void update(int p, int v) { update(1, 1, size, p, v); }
    
    inline
    int query(int p) const { return query(1, 1, size, p); }
} tree, d_tree[N];

void dfs_size(int u, int p) {
    sub[u] = 1;
    for (int i = 0; i < int(adj[u].size()); ++i) {
        int v = adj[u][i];
        if (used[v]) {
            std::swap(adj[u][i--], adj[u].back());
            adj[u].pop_back();
        } else if (v != p) {
            dfs_size(v, u);
            sub[u] = sub[u] + sub[v];
        }
    }
}

int dfs_center(int u, int size) {
    int best = 0;
    for (int v : adj[u])
        if (sub[best] < sub[v] && sub[v] < sub[u])
            best = v;
    int total = size + sub[u];
    if (sub[best] << 1 <= total)
        return u;
    return dfs_center(best, total - sub[best]);
}

void dfs_verts(int u, int p, std::vector<int>& l) {
    l.push_back(u);
    depth[u] = depth[p] + 1;
    for (int v : adj[u])
        if (v != p)
            dfs_verts(v, u, l);
}

inline
int find(const std::vector<int>& v, int x) {
    return std::lower_bound(v.begin(), v.end(), x) - v.begin();
}

void solve(int root) {
    dfs_size(root, 0);
    std::vector<int> vals, depths;
    vals.reserve(sub[root]);
    depths.reserve(sub[root]);
    int center = dfs_center(root, 0);
    depth[center] = 0;
    vals.push_back(tadd[center]);
    depths.push_back(depth[center]);
    d_vals[depth[center]].push_back(tadd[center]);
    for (int u : adj[center]) {
        verts[u].clear();
        dfs_verts(u, center, verts[u]);
        for (int v : verts[u]) {
            vals.push_back(tadd[v]);
            depths.push_back(depth[v]);
            d_vals[depth[v]].push_back(tadd[v]);            
        }
    }
    std::sort(vals.begin(), vals.end());
    std::sort(depths.begin(), depths.end());
    depths.erase(std::unique(depths.begin(), depths.end()), depths.end());
    for (int d : depths) {
        std::sort(d_vals[d].begin(), d_vals[d].end());
        d_tree[d].resize(d_vals[d].size(), -INF);
    }
    tree.resize(sub[root], -INF);
    tree.update(find(vals, tadd[center]) + 1, 0);
    d_tree[0].update(1, -center);
    for (int u : adj[center])
        for (int v : verts[u]) {
            tree.update(index[v] = find(vals, tadd[v]) + 1, depth[v]);
            d_tree[depth[v]].update(d_index[v] = find(d_vals[depth[v]], tadd[v]) + 1, -v);
        }
    for (int t : queries[center]) {
        int z = tree.query(find(vals, t));
        if (ans_dist[t] <= z) {            
            int x = -d_tree[z].query(find(d_vals[z], t));
            if (ans_dist[t] < z || ans_vert[t] > x) {
                ans_vert[t] = x;
            }
            ans_dist[t] = z;
        }
    }
    for (int u : adj[center]) {
        for (int v : verts[u]) {
            tree.update(index[v], -INF);
            d_tree[depth[v]].update(d_index[v], -INF);
        }
        for (int v : verts[u])
            for (int t : queries[v]) {
                int z = tree.query(find(vals, t));
                if (ans_dist[t] <= z + depth[v]) {
                    int x = -d_tree[z].query(find(d_vals[z], t));
                    if (ans_dist[t] < z + depth[v] || ans_vert[t] > x) {
                        ans_vert[t] = x;
                    }
                    ans_dist[t] = z + depth[v];
                }
            }
        for (int v : verts[u]) {
            tree.update(index[v], depth[v]);
            d_tree[depth[v]].update(d_index[v], -v);
        }
    }
    for (int d : depths)
        d_vals[d].clear();
    used[center] = true;
    for (int u : adj[center])
        solve(u);
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n, q;
    std::cin >> n >> q;
    std::fill(ans_dist + 1, ans_dist + q + 1, -1);
    std::fill(ans_vert + 1, ans_vert + q + 1, INF);
    for (int i = 1; i <= q; ++i) {
        char type;
        int arg1, arg2;
        std::cin >> type >> arg1;
        if (type == 'U') {
            std::cin >> arg2;
            adj[arg1].push_back(arg2);
            adj[arg2].push_back(arg1);
            tadd[arg2] = i;
        } else {
            queries[arg1].push_back(i);
            ans_dist[i] = 0;
            ans_vert[i] = arg1;
        }
    }
    solve(1);
    for (int i = 1; i <= q; ++i)
        if (ans_dist[i] != -1)
            std::cout << ans_dist[i] << ' ' << ans_vert[i] << '\n';
}
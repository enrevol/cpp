#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
const int N = 100010;
const short inf = 10010;
 
struct node {
  int all, best, suff, pref;
};
 
int a[N];
int subtree[N], ancestor[N][17], depth[N], heavy[N];
int top[N], csz[N], vps[N], vid[N];
std::vector<int> edge[N], chain[N];
std::vector<short> lazy[N];
std::vector<node> tree[N];
 
void dfs_sz(int u, int p, int d) {
  depth[u] = d, ancestor[u][0] = p, subtree[u] = 1;
  for (int i = 0; i < int(edge[u].size()); ++i) {
    int v = edge[u][i];
    if (v == p) continue;
    dfs_sz(v, u, d + 1);
    subtree[u] += subtree[v];
    if (subtree[v] > subtree[heavy[u]]) heavy[u] = v;
  }
}
 
void dfs_hl(int u, int p, int tp, int cid, int cps, int& cn) {
  top[u] = tp, ++csz[cid], vid[u] = cid, vps[u] = cps;
  chain[cid].push_back(a[u]);
  for (int i = 0; i < int(edge[u].size()); ++i) {
    int v = edge[u][i];
    if (v == p) continue;
    if (v == heavy[u]) {
      dfs_hl(v, u, tp, cid, cps + 1, cn);
    } else {
      ++cn;
      dfs_hl(v, u, u, cn, 1, cn);
    }
  }
}
 
inline int lca(int u, int v) {
  if (depth[u] < depth[v]) std::swap(u, v);
  for (int i = 31 - __builtin_clz(depth[u] - depth[v]); i >= 0; --i)
    if (depth[u] - (1 << i) >= depth[v])
      u = ancestor[u][i];
  if (u == v) return u;
  for (int i = std::__lg(depth[u]); i >= 0; --i)
    if (ancestor[u][i] != ancestor[v][i])
      u = ancestor[u][i], v = ancestor[v][i];
  return ancestor[u][0];
}
 
inline int find(int u, int v) {
  for (int i = 31 - __builtin_clz(depth[u] - depth[v]); i >= 0; --i)
    if (depth[u] - (1 << i) > depth[v])
      u = ancestor[u][i];
  return u;
}
 
inline node merge(const node& x, const node& y) {
  if (x.best < 0) return y;
  if (y.best < 0) return x;
  node res;
  res.all = x.all + y.all;
  res.pref = std::max(x.pref, x.all + y.pref);
  res.suff = std::max(y.suff, y.all + x.suff);
  res.best = std::max(x.best, y.best);
  res.best = std::max(res.best, x.suff + y.pref);
  //res.best = std::max(res.best, res.all);
  //res.best = std::max(res.best, res.pref);
  //res.best = std::max(res.best, res.suff);
  return res;
}
 
inline void make(node& x, int sz, int val) {
  x.all = val * sz;
  if (val > 0) {
    x.best = x.pref = x.suff = x.all;
  } else {
    x.best = x.pref = x.suff = 0;
  }
}
 
void build(int id, int i, int f, int t) {
  if (f == t) {
    make(tree[id][i], 1, chain[id][f - 1]);
  } else {
    int m = (f + t) >> 1;
    build(id, i << 1, f, m);
    build(id, i << 1 | 1, m + 1, t);
    tree[id][i] = merge(tree[id][i << 1], tree[id][i << 1 | 1]);
  }
}
 
inline void push(int id, int i, int f, int t) {
  if (lazy[id][i] < inf) {
    int m = (f + t) >> 1;
    short& v = lazy[id][i];
    make(tree[id][i << 1], m - f + 1, v);
    make(tree[id][i << 1 | 1], t - m, v);
    if (f < m) lazy[id][i << 1] = v;
    if (m + 1 < t) lazy[id][i << 1 | 1] = v;
    v = inf;
  }
}
 
void change(int id, int i, int f, int t, int qf, int qt, int val) {
  push(id, i, f, t);
  if (qf <= f && t <= qt) {
    make(tree[id][i], t - f + 1, val);
    if (f < t) lazy[id][i] = val;
  } else {
    int m = (f + t) >> 1;
    if (qf < m + 1) change(id, i << 1, f, m, qf, qt, val);
    if (qt > m) change(id, i << 1 | 1, m + 1, t, qf, qt, val);
    tree[id][i] = merge(tree[id][i << 1], tree[id][i << 1 | 1]);
  }
}
 
void change(int u, int v, int val) {  
  for ( ; vid[u] != vid[v]; u = top[u])
    change(vid[u], 1, 1, csz[vid[u]], 1, vps[u], val);
  change(vid[u], 1, 1, csz[vid[u]], vps[v], vps[u], val);
}
 
node query(int id, int i, int f, int t, int qf, int qt) {
  push(id, i, f, t);
  if (qf <= f && t <= qt) return tree[id][i];
  int m = (f + t) >> 1;
  if (qt < m + 1) return query(id, i << 1, f, m, qf, qt);
  if (qf > m) return query(id, i << 1 | 1, m + 1, t, qf, qt);
  return merge(query(id, i << 1, f, m, qf, qt), query(id, i << 1 | 1, m + 1, t, qf, qt));  
}
 
node query(int u, int v) {
  node res;
  res.best = -1;
  for ( ; vid[u] != vid[v]; u = top[u])
    res = merge(query(vid[u], 1, 1, csz[vid[u]], 1, vps[u]), res);  
  return merge(query(vid[u], 1, 1, csz[vid[u]], vps[v], vps[u]), res);
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) scanf("%d", a + i);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  dfs_sz(1, 0, 1);
  for (int j = 1; 1 << j <= n; ++j)
    for (int i = 1; i <= n; ++i)
      ancestor[i][j] = ancestor[ancestor[i][j - 1]][j - 1];
  int cn = 1;
  dfs_hl(1, 0, 0, 1, 1, cn);
  for (int i = 1; i <= cn; ++i) {
    tree[i].resize(csz[i] << 2 | 1);
    lazy[i].resize(csz[i] << 2 | 1);
    std::fill(lazy[i].begin(), lazy[i].end(), inf);
    build(i, 1, 1, csz[i]);
  }
  int q;
  for (scanf("%d", &q); q--; ) {
    int k, a, b, c;
    scanf("%d %d %d", &k, &a, &b);
    int t = lca(a, b);
    if (k == 1) {
      node x;
      if (a == t && b == t) {
        x = query(t, t);
      } else if (a == t) {
        x = query(b, a);
      } else {
        int u = find(a, t);
        node path1 = query(a, u);
        node path2 = query(b, t);
        std::swap(path2.pref, path2.suff);
        x = merge(path2, path1);
      }
      printf("%d\n", x.best);
    } else {
      scanf("%d", &c);
      if (a == t && b == t) {
        change(a, a, c);
      } else if (a == t) {
        change(b, a, c);
      } else {
        int u = find(a, t);
        change(a, u, c);
        change(b, t, c);
      }
    }
  }
}
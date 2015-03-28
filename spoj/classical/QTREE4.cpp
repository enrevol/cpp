#include <algorithm>
#include <bitset>
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
const int INF = 1e9;

struct edge {
  int to, dist;
  edge(int to, int dist) : to(to), dist(dist) { }
};

std::vector<edge> ed[N];
bool mark[N];
int sub_sz[N], vps[N], parent[N], color[N], dist[18][N], pos[18][N], depth[N];

struct node1 {  
  int far1, far2, best;
  node1(int far1 = -INF, int far2 = -INF, int best = -INF) : far1(far1), far2(far2), best(best) { }
  inline int query() const { return std::max(best, far1 + far2); }
  friend inline node1 merge(const node1& x, const node1& y) {
    int tmp[] = { x.far1, x.far2, y.far1, y.far2 };
    std::sort(tmp, tmp + 4, std::greater<int>());
    return node1(tmp[0], tmp[1], std::max(x.best, y.best));
  }
};

struct node2 {
  int key;
  node2(int key = -INF) : key(key) { }
  inline int query() const { return key; }
  friend inline node2 merge(const node2& x, const node2& y) {
    return node2(std::max(x.key, y.key));
  }
};

template<typename node>
class IT {
  int sz;
  std::vector<node> arr;
  void update(int i, int f, int t, int p, const node& x) {
    if (f == t) {
      arr[i] = x;
    } else {
      int m = (f + t) >> 1;
      if (p < m + 1) update(i << 1, f, m, p, x);
      else update(i << 1 | 1, m + 1, t, p, x);
      arr[i] = merge(arr[i << 1], arr[i << 1 | 1]);
    }
  }
public:
  IT(int sz = 1) : sz(sz), arr((1 << (std::__lg(sz - 1) + 2)) | 1) { }
  inline void update(int p, const node& x) { update(1, 1, sz, p, x); }  
  inline int query() const { return arr[1].query(); }
};

IT<node1> tr1[N];
IT<node2> tr2[N];

void dfs_size(int u, int p) {
  sub_sz[u] = 1;
  for (int i = 0; i < int(ed[u].size()); ++i) {
    int v = ed[u][i].to;
    if (v == p) continue;
    if (mark[v]) {
      std::swap(ed[u][i], ed[u].back());
      ed[u].pop_back();
      --i;
    } else {
      dfs_size(v, u);
      sub_sz[u] += sub_sz[v];
    }
  }
}

void dfs_dist(int u, int p, int d, int k, int ct, int& tm) {
  depth[u] = k;
  pos[k][u] = ++tm;
  tr2[ct].update(tm, node2(d));
  dist[k][u] = d;
  for (int i = 0; i < int(ed[u].size()); ++i) {
    int v = ed[u][i].to;
    if (v == p) continue;
    if (mark[v]) {
      std::swap(ed[u][i], ed[u].back());
      ed[u].pop_back();
      --i;
    } else {
      dfs_dist(v, u, d + ed[u][i].dist, k, ct, tm);
    }
  }
}

int dfs_center(int u, int p, int anc_sz) {
  int total = sub_sz[u] + anc_sz;
  if (anc_sz << 1 > total + 1) return 0;
  int flag = 1;
  for (int i = 0; i < int(ed[u].size()) && flag; ++i) {
    int v = ed[u][i].to;
    if (v == p) continue;
    if (mark[v]) {
      std::swap(ed[u][i], ed[u].back());
      ed[u].pop_back();
      --i;
    } else {
      flag = sub_sz[v] << 1 <= total + 1;
    }
  }
  if (flag) return u;
  for (int i = 0; i < int(ed[u].size()); ++i) {
    int v = ed[u][i].to;
    if (v == p) continue;
    if (mark[v]) {
      std::swap(ed[u][i], ed[u].back());
      ed[u].pop_back();
      --i;
    } else {
      int x = dfs_center(v, u, total - sub_sz[v]);
      if (x > 0) return x;
    }
  }
  return 0;
}

int build(int depth, int root, int pa, int pos) {  
  dfs_size(root, 0);  
  int ct = dfs_center(root, 0, 0);
  tr1[ct] = IT<node1>(ed[ct].size() + 1);
  tr2[ct] = IT<node2>(sub_sz[root]);
  int tm = 0;
  dfs_dist(root, 0, 0, depth, ct, tm);
  mark[ct] = 1;
  parent[ct] = pa;
  vps[ct] = pos;
  for (int i = 0; i < int(ed[ct].size()); ++i) {
    int v = ed[ct][i].to;
    if (mark[v]) continue;
    int x = build(depth + 1, v, ct, i + 1);
    int far = tr2[x].query();
    int best = tr1[x].query();
    tr1[ct].update(i + 1, node1(far + ed[ct][i].dist, -INF, best));
  }
  tr1[ct].update(ed[ct].size() + 1, node1(0, -INF, 0));
  return ct;
}

inline void change(int u) {
  color[u] ^= 1;
  int k = depth[u];
  tr1[u].update(ed[u].size() + 1, color[u] ? node1() : node1(0, -INF, 0));
  int v = u;
  while (parent[v] > 0) {
    int x = parent[v];
    tr2[v].update(pos[k][u], color[u] ? node2() : node2(dist[k][u]));
    int far = tr2[v].query();
    int best = tr1[v].query();
    tr1[x].update(vps[v], node1(far + ed[x][vps[v] - 1].dist, -INF, best));
    v = x;
    --k;
  }
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output2.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int u, v, c;
    scanf("%d %d %d", &u, &v, &c);
    ed[u].push_back(edge(v, c));
    ed[v].push_back(edge(u, c));
  }
  int ct = build(0, 1, 0, 0);
  int m;
  scanf("%d", &m);
  while (m--) {
    char s[2];
    scanf("%s", s);
    if (*s == 'A') {
      int ans = tr1[ct].query();
      if (ans == -INF) {             
        puts("They have disappeared.");
      } else {
        printf("%d\n", ans);
      }
    } else {
      int p;
      scanf("%d", &p);
      change(p);
    }
  }
}
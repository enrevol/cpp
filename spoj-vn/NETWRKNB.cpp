#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
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
 
struct edge {
  int u, v, c;
} e[101010];
 
struct ssp {
  int i, f, c;
  ssp(int i, int f, int c) : i(i), f(f), c(c) { }
};
 
std::vector<int> ve[101010];
std::vector<ssp> vp[101010];
 
struct sst {
  bool f;
  int i, c, u;
  sst() { }
  sst(bool f, int i, int c, int u) : f(f), i(i), c(c), u(u) { }
  bool operator< (const sst& x) const {
    return c < x.c;
  }
} vt[101010];
 
std::vector<int> vq[101010];
 
int tr[505050];
int zz[505050];
int pos[101010];
 
int cn;
int tn;
int xc[101010];
int h[101010];
int dp[101010][18];
 
int fw[101010];
int te[101010];
int ans[101010];
 
inline int query(int i) {
  int res = 0;
  for ( ; i >= 1; i -= i & -i)
    res += fw[i];
  return res;
}
 
inline void update(int i, int val) {
  for ( ; i <= cn; i += i & -i)
    fw[i] += val;
}
 
inline int getv(int u, int i) {
  edge& x = e[ve[u][i]];
  return u == x.u ? x.v : x.u;
}
 
void dfs(int u, int p, int k) {
  dp[u][0] = p;
  h[u] = k;
  for (size_t i = 0; i < ve[u].size(); ++i) {
    int v = getv(u, i);
    if (v == p) continue;
    dfs(v, u, k + 1);
  }
}
 
void dfsp(int u, int p) {
  for (size_t i = 0; i < vp[u].size(); ++i) {
    ssp& x = vp[u][i];
    ans[x.i] += x.f * query(x.c);
  }
  for (size_t i = 0; i < ve[u].size(); ++i) {
    int v = getv(u, i);
    if (v == p) continue;
    update(e[ve[u][i]].c, 1);
    dfsp(v, u);
    update(e[ve[u][i]].c, -1);
  }
}
 
inline void push(int i, int f, int t) {
  int m = (f + t) >> 1;
  int il = i << 1;
  int ir = i << 1 | 1;
  if (zz[i]) {
    assert(f < t);
    if (f == m) {
      if (vt[f].f) tr[il] += zz[i];
    } else {
      tr[il] += zz[i];
      zz[il] += zz[i];
    }
    if (m + 1 == t) {
      if (vt[t].f) tr[ir] += zz[i];
    } else {
      tr[ir] += zz[i];
      zz[ir] += zz[i];
    }
    zz[i] = 0;
  }
}
 
void update(int i, int f, int t, int p) {
  push(i, f, t);
  if (p <= f) {
    if (f == t) {
      if (vt[f].f) ++tr[i];
    } else {
      ++tr[i];
      ++zz[i];
    }
  } else {
    int il = i << 1;
    int ir = i << 1 | 1;
    int m = (f + t) >> 1;
    if (p < m + 1) update(il, f, m, p);
    update(ir, m + 1, t, p);
  }
}
 
void change(int i, int f, int t, int p) {
  push(i, f, t);
  if (f == t) {
    vt[f].f ^= 1;
  } else {
    int il = i << 1;
    int ir = i << 1 | 1;
    int m = (f + t) >> 1;
    if (p > m) change(ir, m + 1, t, p);
    else change(il, f, m, p);
  }
}
 
int query(int i, int f, int t, int p) {
  push(i, f, t);
  if (f == t) {
    return tr[i];
  } else {
    int il = i << 1;
    int ir = i << 1 | 1;
    int m = (f + t) >> 1;
    if (p > m) return query(ir, m + 1, t, p);
    return query(il, f, m, p);
  }
}
 
void dfst(int u, int p) {
  for (size_t i = 0; i < vq[u].size(); ++i)
    change(1, 1, tn, vq[u][i]);
  for (size_t i = 0; i < ve[u].size(); ++i) {
    int v = getv(u, i);
    if (v == p) continue;
    int c = e[ve[u][i]].c;
    if (pos[c] != -1) update(1, 1, tn, pos[c]);
    dfst(v, u);
  }
  for (size_t i = 0; i < vq[u].size(); ++i)
    change(1, 1, tn, vq[u][i]);
}
 
int lca(int u, int v) {
  if (h[u] < h[v]) std::swap(u, v);
  for (int i = 16; i >= 0; --i)
    if (h[u] - (1 << i) >= h[v])
      u = dp[u][i];
  if (u == v) return u;
  for (int i = 16; i >= 0; --i)
    if (dp[u][i] != dp[v][i]) {
      u = dp[u][i];
      v = dp[v][i];
    }
  return dp[u][0];
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i < n; ++i) {
    scanf("%d %d %d", &e[i].u, &e[i].v, &e[i].c);
    xc[i] = e[i].c;
    ve[e[i].u].push_back(i);
    ve[e[i].v].push_back(i);
  }
  std::sort(xc + 1, xc + n);
  cn = std::unique(xc + 1, xc + n) - xc - 1;
  for (int i = 1; i < n; ++i) {
    e[i].c = std::lower_bound(xc + 1, xc + cn + 1, e[i].c) - xc;
    ++te[e[i].c];
  }
  for (int i = 1; i <= cn; ++i)
    te[i] += te[i - 1];
  dfs(1, 0, 1);
  for (int j = 1; 1 << j <= n; ++j)
    for (int i = 1; i <= n; ++i)
      dp[i][j] = dp[dp[i][j - 1]][j - 1];
  for (int i = 1; i <= m; ++i) {
    char s[5];
    scanf("%s", s);
    if (*s == 'P') {
      int u, v, c;
      scanf("%d %d %d", &u, &v, &c);
      c = std::upper_bound(xc + 1, xc + cn + 1, c) - xc - 1;
      int t = lca(u, v);
      vp[u].push_back(ssp(i, 1, c));
      vp[v].push_back(ssp(i, 1, c));
      vp[t].push_back(ssp(i, -2, c));
    } else {
      int k, c;
      scanf("%d %d", &k, &c);
      c = std::upper_bound(xc + 1, xc + cn + 1, c) - xc - 1;
      edge& x = e[k];
      if (h[x.u] < h[x.v]) {
        vt[++tn] = sst(0, i, c, x.v);
      } else {
        vt[++tn] = sst(1, i, c, x.u);
        ans[i] -= x.c <= c;
      }
    }
  }
  dfsp(1, 0);
  std::sort(vt + 1, vt + tn + 1);
  for (int i = 1; i <= tn; ++i)
    vq[vt[i].u].push_back(i);
  memset(pos, -1, sizeof(pos));
  for (int i = 1; i <= tn; ++i) {
    int& ref = pos[vt[i].c];
    if (ref == -1 || ref > i)
      ref = i;
  }
  for (int i = cn; i >= 1; --i)
    if (pos[i] == -1)
      pos[i] = pos[i + 1];
  dfst(1, 0);
  for (int i = 1; i <= tn; ++i)
    ans[vt[i].i] += query(1, 1, tn, i);
  for (int i = 1; i <= m; ++i)
    printf("%d\n", ans[i]);
}
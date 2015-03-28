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
 
const int w = 10000;
 
int eu[w + 10];
int ev[w + 10];
int ec[w + 10];
std::vector<int> ed[w + 10];
 
int sub[w + 10];
int light[w + 10];
 
int csz[w + 10];
std::vector<int> ch[w + 10];
 
int vid[w + 10];
int vps[w + 10];
int top[w + 10];
 
int eid[w + 10];
int eps[w + 10];
 
int h[w + 10];
int pa[w + 10][15];
 
inline int getv(int u, int i) {
  return eu[i] == u ? ev[i] : eu[i];
}
 
void dfs(int u, int p, int d) {
  h[u] = d;
  pa[u][0] = p;
  sub[u] = 1;
  light[u] = 0;
  int val = 0;
  for (int i = 0; i < int(ed[u].size()); ++i) {
    int v = getv(u, ed[u][i]);
    if (v == p) continue;
    dfs(v, u, d + 1);
    sub[u] += sub[v];
    if (sub[v] > val) {
      light[u] = ed[u][i];
      val = sub[v];
    }
  }
}
 
void dfs(int u, int p, int t, int e, int ci, int cp, int& cn) {
  ++csz[ci];
  vps[u] = eps[e] = cp;
  vid[u] = eid[e] = ci;
  top[u] = t;
  for (int i = 0; i < int(ed[u].size()); ++i) {
    int k = ed[u][i];
    int v = getv(u, k);
    if (v == p) continue;
    if (k == light[u]) {
      dfs(v, u, t, k, ci, cp + 1, cn);
    } else {
      ++cn;
      csz[cn] = 0;
      dfs(v, u, u, k, cn, 1, cn);
    }
  }
}
 
int lca(int u, int v) {
  if (h[u] < h[v]) std::swap(u, v);
  for (int i = 13; i >= 0; --i)
    if (h[u] - (1 << i) >= h[v])
      u = pa[u][i];
  if (u == v) return u;
  int k = std::__lg(h[u]);
  for (int i = k; i >= 0; --i)
    if (pa[u][i] != pa[v][i]) {
      u = pa[u][i];
      v = pa[v][i];
    }
  return pa[u][0];
}
 
void update(int id, int i, int f, int t, int p, int v) {
  if (f == t) {
    ch[id][i] = v;
  } else {
    int m = (f + t) >> 1;    
    if (p < m + 1) update(id, i << 1, f, m, p, v);
    else update(id, i << 1 | 1, m + 1, t, p, v);
    ch[id][i] = std::max(ch[id][i << 1], ch[id][i << 1 | 1]);
  }
}
 
int query(int id, int i, int f, int t, int qf, int qt) {
  if (qf <= f && t <= qt) {
    return ch[id][i];
  } else {
    int m = (f + t) >> 1;
    int il = i << 1;
    int ir = i << 1 | 1;
    if (qt < m + 1) return query(id, il, f, m, qf, qt);
    if (qf > m) return query(id, ir, m + 1, t, qf, qt);    
    return std::max(query(id, il, f, m, qf, qt), query(id, ir, m + 1, t, qf, qt));
  }
}
 
int query(int u, int v) {
  int res = 0;
  while (1) {
    if (vid[u] == vid[v]) {      
      if (vps[v] < vps[u]) {
        int val = query(vid[u], 1, 1, csz[vid[u]], vps[v] + 1, vps[u]);
        res = std::max(res, val);
      }
      break;
    } else {
      int val = query(vid[u], 1, 1, csz[vid[u]], 1, vps[u]);
      res = std::max(res, val);
      u = top[u];      
    }
  }
  return res;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int tt;
  for (scanf("%d", &tt); tt--; ) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      ed[i].clear();
    for (int i = 1; i < n; ++i) {
      scanf("%d %d %d", eu + i, ev + i, ec + i);
      ed[eu[i]].push_back(i);
      ed[ev[i]].push_back(i);
    }
    dfs(1, 0, 1);
    for (int j = 1; 1 << j <= n; ++j)
      for (int i = 1; i <= n; ++i)
        pa[i][j] = pa[pa[i][j - 1]][j - 1];
    int cn = 1;
    csz[cn] = -1;
    dfs(1, 0, 0, 0, 1, 0, cn);
    for (int i = 1; i <= cn; ++i) {
      ch[i].resize(csz[i] * 4 + 1);
      std::fill(ch[i].begin(), ch[i].end(), 0);
    }
    for (int i = 1; i < n; ++i) {
      int ei = eid[i];
      int ep = eps[i];
      update(ei, 1, 1, csz[ei], ep, ec[i]);
    }
    char s[10];
    while (scanf("%s", s)) {
      if (*s == 'D') break;
      int x, y;
      scanf("%d %d", &x, &y);
      if (*s == 'C') {
        int ei = eid[x];
        int ep = eps[x];
        update(ei, 1, 1, csz[ei], ep, y);
      } else {
        int t = lca(x, y);
        int res = std::max(query(x, t), query(y, t));
        printf("%d\n", res);
      }
    }
  }
}
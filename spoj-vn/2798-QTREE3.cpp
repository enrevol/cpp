SPOJ submission 11782060 (C++ 4.3.2) plaintext list. Status: AC, problem QTREE3, contest SPOJVN. By enrevol (What Does The Fox Say?), 2014-06-18 12:16:29.
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
 
const int w = 1e5;
 
std::vector<int> ed[w + 10];
std::vector<int> tr[w + 10];
std::vector<int> ch[w + 10];
bool stt[w + 10];
int vid[w + 10], vps[w + 10], top[w + 10];
int sub[w + 10], light[w + 10], csz[w + 10];
 
inline void update(int id, int i, int f, int t, int p, bool v) {
  if (f == t) {
    // if (v == 0) tr[id][i] = 0;
    // else        tr[id][i] = p;
    tr[id][i] = v * p;    
  } else {
    int m = (f + t) >> 1;
    int l = i << 1;
    int r = i << 1 | 1;
    if (p < m + 1) update(id, l, f, m, p, v);
    else           update(id, r, m + 1, t, p, v);
    if (tr[id][l] > 0) tr[id][i] = tr[id][l];
    else               tr[id][i] = tr[id][r];
  }
}
 
inline int query(int id, int i, int f, int t, int p) {
  if (t <= p) {
    return tr[id][i];
  } else{
    int m = (f + t) >> 1;
    int l = i << 1;
    int r = i << 1 | 1;
    if (p < m + 1) return query(id, l, f, m, p);
    int v = query(id, l, f, m, p);
    if (v > 0) return v;
    return query(id, r, m + 1, t, p);
  }
}
 
inline int dfs(int u, int p) {
  sub[u] = 1;
  int best = 0;
  for (int i = 0; i < int(ed[u].size()); ++i) {
    int v = ed[u][i];
    if (v == p) continue;
    int sz = dfs(v, u);
    sub[u] += sz;
    if (sz > best) {
      best = sz;
      light[u] = v;
    }
  }
  return sub[u];
}
 
inline void dfs(int u, int p, int t, int ci, int cp, int& cn) {
  ++csz[ci];
  top[u] = t;
  vid[u] = ci;
  vps[u] = cp;
  ch[ci].push_back(u);
  for (int i = 0; i < int(ed[u].size()); ++i) {
    int v = ed[u][i];
    if (v == p) continue;
    if (v == light[u]) {
      dfs(v, u, t, ci, cp + 1, cn);      
    } else {
      ++cn;
      ch[cn].push_back(0);
      dfs(v, u, u, cn, 1, cn);
    }
  }
}
 
int cid[30];
int cps[30];
 
inline int query(int u) {
  int sz = 0;
  for (int i = u; i; i = top[i]) {
    ++sz;
    cid[sz] = vid[i];
    cps[sz] = vps[i];
  }
  for (int i = sz; i; --i) {
    int id = cid[i];
    int ps = cps[i];
    int v = query(id, 1, 1, csz[id], ps);
    if (v) return ch[id][v];
  }
  return -1;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, q;
  scanf("%d %d", &n, &q);
  for (int i = 1, u, v; i < n; ++i) {
    scanf("%d %d", &u, &v);
    ed[u].push_back(v);
    ed[v].push_back(u);
  }
  dfs(1, 0);
  int cn = 1;
  ch[1].push_back(0);
  dfs(1, 0, 0, 1, 1, cn);
  for (int i = 1; i <= cn; ++i)
    tr[i].resize(csz[i] * 4 + 1);
  for (int k, u; q--; ) {
    scanf("%d %d", &k, &u);
    if (k == 0) {
      stt[u] ^= 1;
      update(vid[u], 1, 1, csz[vid[u]], vps[u], stt[u]);
    } else {
      int res = query(u);
      printf("%d\n", res);
    }
  }
}
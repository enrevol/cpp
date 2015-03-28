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
 
const int inf = 0x3c3c3c3c;
 
std::vector<int> ed[505];
int a[505];
int cp[505][505];
int q[505];
int dist[505];
int pos[505];
 
inline void add(int u, int v, int c) {
  ed[u].push_back(v);
  ed[v].push_back(u);
  cp[u][v] = c;
}
 
bool bfs(int src, int dst) {
  memset(dist, -1, sizeof(dist));
  dist[src] = 0;
  int sz = 0;
  q[++sz] = src;
  for (int i = 1; i <= sz; ++i) {
    int u = q[i];
    for (int j = 0; j < int(ed[u].size()); ++j) {
      int v = ed[u][j];
      if (dist[v] == -1 && cp[u][v] > 0) {
        dist[v] = dist[u] + 1;
        q[++sz] = v;
      }
    }
  }
  return dist[dst] >= 0;  
}
 
int dfs(int u, int dst, int f) {
  if (u == dst) return f;
  for (int& i = pos[u]; i < int(ed[u].size()); ++i) {
    int v = ed[u][i];
    if (cp[u][v] > 0 && dist[v] == dist[u] + 1) {
      if (int df = dfs(v, dst, std::min(f, cp[u][v]))) {
        cp[u][v] -= df;
        cp[v][u] += df;
        return df;
      }
    }    
  }
  return 0;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  int src = n + 1;
  int dst = n + 2;
  int tot = 0;
  for (int i = 1, v; i <= n; ++i) {
    scanf("%d", &v);
    if (v > 0) {
      add(src, i, v);
      tot += v;
    } else {
      add(i, dst, -v);
    }
  }
  int m;
  scanf("%d", &m);
  for (int u, v; m--; ) {
    scanf("%d %d", &u, &v);
    add(u, v, inf);
  }
  int ans = 0;
  while (bfs(src, dst)) {
    memset(pos, 0, sizeof(pos));
    while (int psh = dfs(src, dst, inf))
      ans += psh;
  }
  printf("%d", tot - ans);
}
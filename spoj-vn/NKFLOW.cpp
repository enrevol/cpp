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
 
const int w = 1000;
 
struct edge {
  int to;
  int rev;
  int cap;
};
 
int n, m, s, t;
 
std::vector<edge> ed[w + 10];
 
int pos[w + 10];
int dist[w + 10];
int q[w + 10];
 
inline void add(int u, int v, int cap) {
  edge a = { v, int(ed[v].size()), cap };
  edge b = { u, int(ed[u].size()), 0 };
  ed[u].push_back(a);
  ed[v].push_back(b);
}
 
bool bfs() {
  memset(dist + 1, -1, n << 2);
  int qs = 0;
  q[++qs] = s;
  dist[s] = 0;  
  for (int i = 1; i <= qs; ++i) {
    int u = q[i];
    int sz = int(ed[u].size());
    for (int j = 0; j < sz; ++j) {
      const edge& e = ed[u][j];
      int v = e.to;
      if (dist[v] < 0 && e.cap > 0) {
        dist[v] = dist[u] + 1;
        q[++qs] = v;
      }
    }
  }
  return dist[t] >= 0;
}
 
int dfs(int u, int f) {
  if (u == t) return f;
  int sz = int(ed[u].size());
  for (int& i = pos[u]; i < sz; ++i) {
    edge& e = ed[u][i];
    int v = e.to;
    if (dist[v] == dist[u] + 1 && e.cap > 0) {
      int df = dfs(v, std::min(f, e.cap));
      if (df > 0) {
        e.cap -= df;
        ed[v][e.rev].cap += df;
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
  scanf("%d %d %d %d", &n, &m, &s, &t);
  for (int i = 1, u, v, c; i <= m; ++i) {
    scanf("%d %d %d", &u, &v, &c);
    add(u, v, c);
  }
  int ans = 0;
  while (bfs()) {
    memset(pos + 1, 0, n << 2);
    while (int d = dfs(s, 1e9))
      ans += d;      
  }
  printf("%d", ans);
}
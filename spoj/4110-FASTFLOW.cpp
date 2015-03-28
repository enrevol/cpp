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
 
typedef unsigned short     u16;
typedef unsigned           u32;
typedef unsigned long long u64;
 
const u16 inf16 = 0x3c3c;
const u32 inf32 = 0x3c3c3c3c;
const u16 w     = 5000;
 
u16 n, m;
 
struct edge {
  u16 to, rev;
  u32 cap;
};
 
std::vector<edge> ed[w + 10];
 
inline void add(u16 u, u16 v, u32 cap) {
  edge a = { v, u16(ed[v].size()), cap };
  edge b = { u, u16(ed[u].size()), cap };
  ed[u].push_back(a);
  ed[v].push_back(b);
}
 
u16 dist[w + 10];
u16 q[w + 10];
u16 pos[w + 10];
 
bool bfs() {
  memset(dist + 1, 0x3c, n << 1);
  dist[1] = 0;
  u16 qs = 0;
  q[++qs] = 1;
  for (u16 i = 1; i <= qs; ++i) {
    u16 u = q[i];    
    for (u16 j = 0; j < ed[u].size(); ++j) {
      const edge& e = ed[u][j];
      u16 v = e.to;
      if (dist[v] == inf16 && e.cap > 0) {
        dist[v] = dist[u] + 1;
        q[++qs] = v;
      }
    }
  }
  return dist[n] < inf16;
}
 
u32 dfs(u16 u, u32 f) {
  if (u == n) return f;
  for (u16& i = pos[u]; i < ed[u].size(); ++i) {
    edge& e = ed[u][i];
    u16 v = e.to;
    if (dist[v] == dist[u] + 1 && e.cap > 0) {
      u32 df = dfs(v, std::min(f, e.cap));
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
  scanf("%hu %hu", &n, &m);
  for (u16 i = 1; i <= m; ++i) {
    u16 u, v;
    u32 c;
    scanf("%hu %hu %u", &u, &v, &c);
    if (u == v) continue;
    add(u, v, c);
  }
  u64 ans = 0;
  while (bfs()) {
    memset(pos + 1, 0, n << 1);
    while (u32 d = dfs(1, inf32))
      ans += d;
  }
  printf("%llu", ans);
}
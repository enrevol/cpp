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
 
const int w = 100000;
 
std::vector<int> ed[w + 10];
 
int n, m, p;
 
int match[w + 10];
int dist[w + 10];
int q[w + 10];
 
bool bfs() {
  memset(dist, -1, sizeof(dist));
  int qs = 0;
  for (int i = 1; i <= n; ++i)
    if (!match[i]) {
      q[++qs] = i;
      dist[i] = 0;
    }
  for (int i = 1; i <= qs; ++i) {
    int u = q[i];
    if (u == 0) continue;
    int sz = int(ed[u].size());
    for (int i = 0; i < sz; ++i) {
      int v = ed[u][i];
      if (dist[match[v]] == -1) {
        dist[match[v]] = dist[u] + 1;
        q[++qs] = match[v];
      }
    }
  }
  return dist[0] != -1;
}
 
bool dfs(int u) {
  if (u == 0) return 1;
  int sz = int(ed[u].size());
  for (int i = 0; i < sz; ++i) {
    int v = ed[u][i];
    if (dist[match[v]] == dist[u] + 1 && dfs(match[v])) {
      match[v] = u;
      match[u] = v;
      return 1;
    }
  }
  dist[u] = -1;
  return 0;
}
 
int hopcroft_karp() {
  int res = 0;
  while (bfs())
    for (int i = 1; i <= n; ++i)
      res += !match[i] && dfs(i);
  return res;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  scanf("%d %d %d", &n, &m, &p);
  for (int i = 1, u, v; i <= p; ++i) {
    scanf("%d %d", &u, &v);
    ed[u].push_back(v + n);
  }
  printf("%d", hopcroft_karp());
}
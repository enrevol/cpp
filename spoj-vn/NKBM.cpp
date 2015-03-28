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

const int N = 2010;

struct edge {
  int to, rev, cap;
  edge(int to, int rev, int cap) : to(to), rev(rev), cap(cap) { }
};

std::vector<edge> ed[N];
int q[N], dist[N], pos[N];

inline void add(int src, int dst, int cap) {
  edge x(dst, int(ed[dst].size()), cap);
  edge y(src, int(ed[src].size()), 0);
  ed[src].push_back(x);
  ed[dst].push_back(y);
}

bool bfs(int src, int dst) {
  memset(dist, -1, sizeof(dist));
  dist[src] = 0;
  int sz = 0;
  q[sz++] = src;
  for (int qi = 0; qi < sz; ++qi) {
    int u = q[qi];
    for (int i = 0; i < int(ed[u].size()); ++i) {
      int v = ed[u][i].to;
      if (dist[v] < 0 && ed[u][i].cap) {
        dist[v] = dist[u] + 1;
        q[sz++] = v;
      }
    }
  }
  return dist[dst] >= 0;
}

bool dfs(int u, int dst) {
  if (u == dst) return 1;
  for (int& i = pos[u]; i < int(ed[u].size()); ++i) {
    edge& e = ed[u][i];
    int v = e.to;
    if (dist[v] == dist[u] + 1 && e.cap && dfs(v, dst)) {
      --e.cap;
      ++ed[v][e.rev].cap;
      return 1;
    }
  }
  return 0;
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int n, m, k;
  std::cin >> n >> m >> k;
  int src = n + m + 1;
  int dst = n + m + 2;
  // 1......n
  // n+1..n+m
  for (int u, v; k--; ) {
    std::cin >> u >> v;
    add(u, n + v, 1);
  }
  for (int i = 1; i <= n; ++i) add(src, i, 1);
  for (int i = 1; i <= m; ++i) add(n + i, dst, 1);
  int ans = 0;
  while (bfs(src, dst)) {
    memset(pos, 0, sizeof(pos));
    while (dfs(src, dst)) ++ans;
  }
  std::cout << ans;
}

// Dijkstra Algorithm
// Single-src shortest path for graph with non-negative edge cost
// Complexity: O(|E| + |V| * Log|V|)
// Problem: 1301 - FLOYD
 
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
 
struct ele {
  int dst;
  int dist;
  bool operator< (const ele& x) const {
    return dist > x.dist;
  }
};
 
std::vector<ele> ed[w + 10];
int dist[w + 10];
int pa[w + 10];
 
inline void add(int u, int v, int c, bool directed = 0) {
  ele x = { v, c };  
  ed[u].push_back(x);
  if (directed) return;
  ele y = { u, c };
  ed[v].push_back(y);
}
 
int dijkstra(int src, int dst) {
  ele x = { src, 0 };
  std::priority_queue<ele> q;
  q.push(x);
  memset(dist, -1, sizeof(dist));
  dist[src] = 0;
  while (!q.empty()) {
    int u = q.top().dst;
    int uc = q.top().dist;
    q.pop();
    if (uc == dist[u]) {
      for (int i = 0; i < int(ed[u].size()); ++i) {
        int v = ed[u][i].dst;
        int vc = ed[u][i].dist;
        int tc = vc + uc;
        if (dist[v] == -1 || dist[v] > tc) {
          pa[v] = u;
          dist[v] = tc;
          ele x = { v, tc };
          q.push(x);
        }
      }
    }
  }
  return dist[dst];
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int tt;
  for (scanf("%d", &tt); tt--; ) {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i)
      ed[i].clear();
    for (int u, v, c; m--; ) {
      scanf("%d %d %d", &u, &v, &c);
      add(u, v, c, 1);
    }
    int src, dst;
    scanf("%d %d", &src, &dst);
    int val = dijkstra(src, dst);
    if (val == -1) {
      puts("NO");
    } else {
      printf("%d\n", val);
    }
  }
}
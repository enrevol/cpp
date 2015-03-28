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
 
const int N = 505;
const int MAX = 500 * 10000;
 
struct edge {
  int v, t, c;
  edge(int v, int t, int c) : v(v), t(t), c(c) { }
};
 
struct ele {
  int u, c;
  ele(int u, int c) : u(u), c(c) { }
  bool operator<(const ele& x) const {
    return c > x.c;
  }
};
 
int b[N], dist[N];
std::vector<edge> ed[N], ev[N];
 
void dijkstra(int src) {
  memset(dist, -1, sizeof(dist));
  dist[src] = 0;
  std::priority_queue<ele> q;
  q.push(ele(src, 0));
  while (!q.empty()) {
    int u = q.top().u;
    int c = q.top().c;
    q.pop();
    if (c != dist[u]) continue;
    for (int i = 0; i < int(ed[u].size()); ++i) {
      int v = ed[u][i].v;
      int t = c + ed[u][i].t;
      if (dist[v] == -1 || dist[v] > t) {
        dist[v] = t;
        q.push(ele(v, t));
      }
    }
  }
}
 
struct cmp {
  bool operator()(const ele& x, const ele& y) const {
    return x.c < y.c;
  }
};
 
bool check(int val, int src, int dst) {
  memset(dist, -1, sizeof(dist));
  dist[src] = val;
  std::priority_queue<ele, std::vector<ele>, cmp> q;
  q.push(ele(1, val));
  while (!q.empty()) {
    int u = q.top().u;
    int c = q.top().c;
    q.pop();
    if (c != dist[u]) continue;
    if (b[u]) c = val;
    for (int i = 0; i < int(ev[u].size()); ++i) {
      int v = ev[u][i].v;
      int t = c - ev[u][i].c;
      if (t >= 0) {
        if (dist[v] == -1 || dist[v] < t) {
          dist[v] = t;
          q.push(ele(v, t));
        }
      }
    }
  }
  return dist[dst] != -1;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int n;
  std::cin >> n;
  for (int i = 1; i <= n; ++i)
    std::cin >> b[i];
  int m;
  std::cin >> m;
  for (int u, v, t, c; m--; ) {
    std::cin >> u >> v >> t >> c;
    ed[u].push_back(edge(v, t, c));
    ed[v].push_back(edge(u, t, c));
  }
  dijkstra(1);
  for (int i = 1; i <= n; ++i) {
    int c = dist[i];
    for (int j = 0; j < int(ed[i].size()); ++j) {
      int v = ed[i][j].v;
      int t = c + ed[i][j].t;
      if (t == dist[v]) {
        ev[i].push_back(ed[i][j]);
      }
    }
  }
  int ans = MAX;
  for (int f = 1, t = MAX; f <= t; ) {
    int m = (f + t) >> 1;
    if (check(m, 1, n)) {
      ans = m;
      t = m - 1;
    } else {
      f = m + 1;
    }
  }
  printf("%d", ans);
}
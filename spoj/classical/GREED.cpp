#include <algorithm>
#include <bitset>
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

const int N = 510;
const int INF = 1e9;

struct edge {
  int to, rev, f, cap, cost;
  edge(int to, int rev, int cap, int cost) :
    to(to), rev(rev), f(0), cap(cap), cost(cost) { }
};

std::vector<edge> ed[N];
int cnt[N], pot[N], dist[N], pred_v[N], pred_e[N];

inline void add(int u, int v, int cap, int cost) {
  edge x(v, int(ed[v].size()), cap, cost);
  edge y(u, int(ed[u].size()), 0, -cost);
  ed[u].push_back(x);
  ed[v].push_back(y);
}

struct ele {
  int to, dist;
  ele(int to, int dist) : to(to), dist(dist) { }
  bool operator<(const ele& e) const {
    return dist > e.dist;
  }
};

int min_cost_max_flow(int src, int dst) {
  memset(pot, 0, sizeof(pot));
  int fcost = 0;
  int flow = 0;
  for (;;) {
    std::fill(dist, dist + dst + 1, INF);
    dist[src] = 0;
    std::priority_queue<ele> q;
    q.push(ele(src, 0));
    while (!q.empty()) {
      int u = q.top().to;
      int d = q.top().dist;
      q.pop();
      if (d != dist[u]) continue;
      for (int i = 0; i < int(ed[u].size()); ++i) {
        edge& e = ed[u][i];
        if (e.f < e.cap) {
          int v = e.to;
          int t = dist[u] + e.cost + pot[u] - pot[v];
          if (dist[v] > t) {
            dist[v] = t;
            pred_v[v] = u;
            pred_e[v] = i;
            q.push(ele(v, t));
          }
        }
      }
    }
    if (dist[dst] == INF) return fcost;
    ++flow;
    for (int i = src; i <= dst; ++i) {
      pot[i] += dist[i];
    }
    for (int u = dst, v; u != src; u = v) {
      v = pred_v[u];
      edge& e = ed[v][pred_e[u]];
      ++e.f;
      --ed[u][e.rev].f;
      fcost += e.cost;
    }
  }
  return fcost;
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);
    int src = 0, dst = n + 1;
    for (int i = src; i <= dst; ++i) {
      ed[i].clear();
    }
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; ++i) {
      int v;
      scanf("%d", &v);
      ++cnt[v];
    }
    for (int i = 1; i <= n; ++i) {
      if (cnt[i]) {
        add(src, i, cnt[i], 0);
      }
      add(i, dst, 1, 0);
    }
    int m;
    scanf("%d", &m);
    while (m--) {
      int u, v;
      scanf("%d %d", &u, &v);
      add(u, v, INF, 1);
      add(v, u, INF, 1);
//      edge x(v, int(ed[v].size()), INF, 1);
//      edge y(u, int(ed[u].size()), INF, 1);
//      ed[u].push_back(x);
//      ed[v].push_back(y);
    }
    int ans = min_cost_max_flow(src, dst);
    printf("%d\n", ans);
  }
}
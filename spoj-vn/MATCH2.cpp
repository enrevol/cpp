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

const int N = 210 * 2;
const int INF = 1e9;

struct edge {
  int to, rev, cost, cap, f;
  edge(int to, int rev, int cost, int cap) :
    to(to), rev(rev), cost(cost), cap(cap), f(0) { }
};

std::vector<edge> ed[N];
int dist[N], pot[N], pred_v[N], pred_e[N];

void add(int u, int v, int cost, int cap) {
  edge x(v, int(ed[v].size()), cost, cap);
  edge y(u, int(ed[u].size()), -cost, 0);
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
  int flow = 0;
  int fcost = 0;
  while (flow < dst - 1) {
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
    if (dist[dst] == INF) break;
    for (int i = src; i <= dst; ++i) {
      pot[i] += dist[i];
    }
    ++flow;
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
  int n;
  scanf("%d", &n);
  int src = 0;
  int dst = n + n + 1;
  for (int i = 1; i <= n; ++i) {
    add(src, i, 0, 1);
    add(i + n, dst, 0, 1);
  }
  for (int u, v, c; ~scanf("%d %d %d", &u, &v, &c); ) {
    add(u, v + n, c, 1);
  }  
  int fcost = min_cost_max_flow(src, dst);
  printf("%d\n", fcost);
  for (int i = 1; i <= n; ++i) {
    int v = 0;
    for (int j = 0; j < int(ed[i].size()) && !v; ++j) {
      edge& e = ed[i][j];
      if (n + 1 <= e.to && e.to <= n + n) {
        if (e.f) {
          v = e.to - n;
        }
      }
    }
    printf("%d %d\n", i, v);
  }
}

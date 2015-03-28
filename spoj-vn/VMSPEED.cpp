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
const double EPS = 1e-7;

inline bool eq(double x, double y) {
  return fabs(x - y) <= EPS;
}
 
struct edge {
  int v, s, t;
  double k;
  edge(int v, int s, int t) : v(v), s(s), t(t) { }
};

int n, m;
int cnt[N];
bool mark[N], vis[N], reach[N];
double memo[N];
std::vector<edge> ed[N];

bool check(double val) {  
  for (int i = 1; i <= n; ++i)
    for (int j = 0; j < int(ed[i].size()); ++j)
      ed[i][j].k = ed[i][j].s / val - ed[i][j].t;
  memset(mark, 0, sizeof(mark));
  memset(cnt, 0, sizeof(cnt));
  memset(vis, 0, sizeof(vis));
  memo[1] = 0, vis[1] = mark[1] = 1;
  std::queue<int> q;
  q.push(1);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    ++cnt[u];
    if (cnt[u] > n) {
      if (reach[u]) return 1;
      continue;
    }
    mark[u] = 0;
    for (int i = 0; i < int(ed[u].size()); ++i) {
      int v = ed[u][i].v;
      double t = memo[u] + ed[u][i].k;
      if (vis[v] == 0 || (vis[v] == 1 && t < memo[v] && !eq(t, memo[v]))) {
        vis[v] = 1;
        if (v == n && (t < 0 || eq(t, 0))) return 1;
        memo[v] = t;
        if (mark[v] == 0) {
          mark[v] = 1;
          q.push(v);
        }
      }
    }
  }
  assert(vis[n] == 1);
  assert(memo[n] > 0 && !eq(memo[n], 0));
  return memo[n] < 0 || eq(memo[n], 0);
}

bool bfs(int src, int dst) {
  std::queue<int> q;
  memset(vis, 0, sizeof(vis));
  vis[src] = 1;
  q.push(src);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < int(ed[u].size()); ++i) {
      int v = ed[u][i].v;
      if (vis[v] == 0) {
        if (v == dst) return 1;
        vis[v] = 1;
        q.push(v);
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
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int u, v, s, t;
    scanf("%d %d %d %d", &u, &v, &s, &t);
    ed[u].push_back(edge(v, s, t));
  }
  for (int i = 1; i <= n; ++i)
    reach[i] = bfs(i, n);
  if (reach[1] == 0) {
    puts("-1");
    fprintf(stderr, "non-connected");
  } else {
    double ans = -1;
    double f = 0, t = 1e8 + 1;
    for (int i = 1; i < 50; ++i) {
      double m = (f + t) * 0.5;
      if (check(m)) ans = t = m;
      else f = m;
    }
    printf("%.10lf", ans);
  }
}

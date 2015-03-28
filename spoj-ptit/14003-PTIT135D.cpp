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
 
struct edge {
  int t, c, k;
  edge(int t, int c) : t(t), c(c) { }
  edge(int t, int c, int k) : t(t), c(c), k(k) { }
  bool operator< (const edge& x) const {
    return c > x.c;
  }
};
 
std::vector<edge> ve[1010];
 
int dist[1010];
int p[1010];
 
const int inf = 1e9;
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, m;
  scanf("%d %d", &n, &m);
  int a, b, k, g;
  scanf("%d %d %d %d", &a, &b, &k, &g);
  for (int i = 1; i <= g; ++i)
    scanf("%d", p + i);
  for (int i = 1; i <= m; ++i) {
    int u, v, c;
    scanf("%d %d %d", &u, &v, &c);
    ve[u].push_back(edge(v, c, -inf));
    ve[v].push_back(edge(u, c, -inf));
  }
  k = -k;
  for (int i = 1; i < g; ++i) {
    {
      std::vector<edge>& vx = ve[p[i]];
      for (size_t j = 0; j < vx.size(); ++j)
        if (vx[j].t == p[i + 1]) {
          vx[j].k = k;
          break;
        }
    }
    {
      std::vector<edge>& vx = ve[p[i + 1]];
      for (size_t j = 0; j < vx.size(); ++j)
        if (vx[j].t == p[i]) {
          vx[j].k = k;
          k += vx[j].c;
          break;
        }
    }
  }
  memset(dist, -1, sizeof(dist));
  std::priority_queue<edge> que;
  dist[a] = 0;
  que.push(edge(a, 0));
  while (!que.empty()) {
    edge t = que.top();
    que.pop();
    int& ref = dist[t.t];
    if (ref > t.c) continue;
    std::vector<edge>& vx = ve[t.t];
    for (size_t i = 0; i < vx.size(); ++i) {
      edge& x = vx[i];
      int& dest = dist[x.t];
      int tot = -1;
      if (ref < x.k || ref >= x.k + x.c) {
        tot = ref + x.c;
      } else {
        tot = x.k + x.c + x.c;
      }
      if (dest == -1 || dest > tot) {
        dest = tot;
        que.push(edge(x.t, tot));
      }
    }
  }
  assert(dist[b] != -1);
  printf("%d", dist[b]);
}
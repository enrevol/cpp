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
 
const int N = 10010;
 
typedef std::pair<int, int> p2;
 
std::vector<p2> ed[N], ev[N];
int dsrc[N], ddst[N];
 
struct cmp {
  bool operator()(const p2& x, const p2& y) {
    return x.first > y.first;
  }
};
 
void dijkstra(int src, std::vector<p2> ed[], int dist[]) {
  memset(dist, -1, N << 2);
  dist[src] = 0;
  std::priority_queue<p2, std::vector<p2>, cmp> q;
  q.push(p2(0, src));
  while (!q.empty()) {
    int u = q.top().second;
    int c = q.top().first;
    q.pop();
    if (c > dist[u]) continue;
    for (int i = 0; i < int(ed[u].size()); ++i) {
      int v = ed[u][i].first;
      int d = c + ed[u][i].second;
      if (dist[v] == -1 || dist[v] > d) {
        dist[v] = d;
        q.push(p2(d, v));
      }
    }
  }
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int tt;
  for (scanf("%d", &tt); tt--; ) {
    int n, m, k, src, dst;
    scanf("%d %d %d %d %d", &n, &m, &k, &src, &dst);
    for (int i = 1; i <= n; ++i) {
      ed[i].clear();
      ev[i].clear();
    }
    for (int i = 1; i <= m; ++i) {
      int u, v, c;
      scanf("%d %d %d", &u, &v, &c);
      ed[u].push_back(p2(v, c));
      ev[v].push_back(p2(u, c));
    }
    dijkstra(src, ed, dsrc);    
    dijkstra(dst, ev, ddst);
    int ans = dsrc[dst];
    for (int i = 1; i <= k; ++i) {
      int u, v, c;
      scanf("%d %d %d", &u, &v, &c);
      if (dsrc[u] != -1 && ddst[v] != -1) {
        int tot = dsrc[u] + ddst[v] + c;
        if (ans == -1 || ans > tot) ans = tot;
      }
      if (dsrc[v] != -1 && ddst[u] != -1) {
        int tot = dsrc[v] + ddst[u] + c;
        if (ans == -1 || ans > tot) ans = tot;
      }
    }
    printf("%d\n", ans);
  }
}
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

const int N = 110;

struct edge {
  int to, dist, cost;
  edge(int to, int dist, int cost) : to(to), dist(dist), cost(cost) { }
  bool operator<(const edge& x) const {
    return dist > x.dist;
  }
};

int dp[N][N * N];
std::vector<edge> ed[N];

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int tt;
  for (scanf("%d", &tt); tt--; ) {
    int k, n, m;
    scanf("%d %d %d", &k, &n, &m);
    for (int i = 1; i <= n; ++i) ed[i].clear();
    for (int i = 1; i <= m; ++i) {
      int u, v, d, c;
      scanf("%d %d %d %d", &u, &v, &d, &c);
      ed[u].push_back(edge(v, d, c));
    }
    memset(dp, -1, sizeof(dp));
    std::priority_queue<edge> q;
    q.push(edge(1, 0, 0));
    dp[1][0] = 0;
    while (!q.empty()) {
      const edge& e = q.top();
      int u = e.to;
      int d = e.dist;
      int c = e.cost;
      //fprintf(stderr, "%d %d %d\n", u, d, c);
      q.pop();
      if (d > dp[u][c]) continue;
      for (int i = 0; i < int(ed[u].size()); ++i) {
        int v = ed[u][i].to;
        int nd = ed[u][i].dist + d;
        int nc = ed[u][i].cost + c;        
        if (nc <= k && (dp[v][nc] < 0 || dp[v][nc] > nd)) {
          dp[v][nc] = nd;
          q.push(edge(v, nd, nc));
        }
      }
    }
    int ans = -1;
    for (int i = 0; i <= k; ++i)
      if (dp[n][i] != -1 && (ans == -1 || ans > dp[n][i]))
        ans = dp[n][i];
    printf("%d\n", ans);
  }
}

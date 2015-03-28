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
 
const int N = 20010;

std::vector<int> ed[N];
bool vis[N], mark[N];
int q[N], pred[N], dist[N], pos[N], path[N];

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output2.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);  
  int n, m, src, dst;
  scanf("%d %d %d %d", &n, &m, &src, &dst);
  for (int i = 1; i <= m; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    ed[u].push_back(v);
  }
  q[1] = src;
  dist[src] = 1;
  for (int i = 1, sz = 1; i <= sz && !dist[dst]; ++i) {
    int u = q[i];
    for (int j = 0; j < int(ed[u].size()); ++j) {
      int v = ed[u][j];
      if (!dist[v]) {
        dist[v] = dist[u] + 1;
        pred[v] = u;
        q[++sz] = v;
      }
    }
  }
  assert(dist[dst]);
  int length = dist[dst];
  //fprintf(stderr, "length = %d\n", length);
  for (int u = dst, k = length; k > 0; u = pred[u], --k) {
    path[k] = u;
    pos[u] = k;
    vis[u] = 1;
  }
  int ans = 0;
  for (int last = 1, best = 2; last != length; mark[best++] = 1) {
    //fprintf(stderr, "last = %d best = %d\n", last, best);
    while (last != best) {
      int sz = 0;
      while (last < best) q[++sz] = path[last++];
      for (int i = 1; i <= sz; ++i) {
        int u = q[i];
        for (int j = 0; j < int(ed[u].size()); ++j) {
          int v = ed[u][j];
          best = std::max(best, pos[v]);
          if (!vis[v]) {
            vis[v] = 1;
            if (v != dst) q[++sz] = v;
          }
        }
      }
    }
  }
  for (int i = 2; i < length; ++i)
    ans += mark[i];
  printf("%d", ans);
}

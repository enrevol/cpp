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
 
const int w = 1000;
 
std::vector<int> ed[w + 10];
int dp[w + 10][10];
int h[w + 10];
 
void dfs(int u, int d) {
  h[u] = d;
  int sz = int(ed[u].size());
  for (int i = 0; i < sz; ++i)
    dfs(ed[u][i], d + 1);
}
 
int lca(int u, int v) {
  if (h[u] < h[v]) std::swap(u, v);
  for (int i = 9; i >= 0; --i)
    if (h[u] - (1 << i) >= h[v])
      u = dp[u][i];
  if (u == v) return u;
  for (int i = 9; i >= 0; --i)
    if (dp[u][i] != dp[v][i]) {
      u = dp[u][i];
      v = dp[v][i];
    }
  return dp[u][0];
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int tt;
  scanf("%d", &tt);
  for (int ti = 1; ti <= tt; ++ti) {        
    int n;
    scanf("%d", &n);
    for (int i = 1, k, v; i <= n; ++i) {
      ed[i].clear();
      for (scanf("%d", &k); k--; ) {
        scanf("%d", &v);
        ed[i].push_back(v);
        dp[v][0] = i;
      }
    }
    int root = 0;
    for (int i = 1; i <= n && !root; ++i)
      if (dp[i][0] == 0)
        root = i;
    dfs(root, 1);
    for (int j = 1; j < 10; ++j)
      for (int i = 1; i <= n; ++i)
        dp[i][j] = dp[dp[i][j - 1]][j - 1];
    int q, u, v;
    printf("Case %d:\n", ti);
    for (scanf("%d", &q); q--; ) {
      scanf("%d %d", &u, &v);
      printf("%d\n", lca(u, v));
    }
  }
}
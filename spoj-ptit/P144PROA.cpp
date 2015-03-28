#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
typedef std::pair<int, int> p2;
 
std::vector<p2> e[101010];
int p[101010][20], h[101010];
long long d[101010];
 
void dfs(int u, int v, int k, long long t) {
  h[u] = k;
  p[u][0] = v;
  d[u] = t;
  for (size_t i = 0; i < e[u].size(); ++i)
    if (e[u][i].first != v)
      dfs(e[u][i].first, u, k + 1, t + e[u][i].second);
}
 
int lca(int u, int v) {
  if (h[u] < h[v]) std::swap(u, v);
  for (int i = 18; i >= 0; --i)
    if (h[u] - (1 << i) >= h[v])
      u = p[u][i];
  if (u == v) return u;
  for (int i = 18; i >= 0; --i)
    if (p[u][i] != p[v][i]) {
      u = p[u][i];
      v = p[v][i];
    }
  return p[u][0];
}  
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  while (1) {
    scanf("%d", &n);
    if (n == 0) break;
    for (int i = 1; i <= n; ++i)
      e[i].clear();
    int u, v;
    for (int i = 2; i <= n; ++i) {
      scanf("%d %d", &u, &v);
      ++u;
      e[i].push_back(p2(u, v));
      e[u].push_back(p2(i, v));
    }
    dfs(1, 0, 0, 0);
    for (int j = 1; 1 << j <= n; ++j)
      for (int i = 1; i <= n; ++i)
        p[i][j] = p[p[i][j - 1]][j - 1];
    int q;
    scanf("%d", &q);
    while (q--) {
      scanf("%d %d", &u, &v);
      ++u;
      ++v;
      int t = lca(u, v);
      printf("%lld ", d[u] + d[v] - (d[t] << 1));
    }
    putchar('\n');
  }
} 
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
std::vector<int> e[101];
int d[101];
 
void dfs(int k, int u) {
  if (u == k) return;
  if (d[u]) return;
  d[u] = 1;
  for (size_t i = 0; i < e[u].size(); ++i)
    dfs(k, e[u][i]);
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n, m, u, v;
    scanf("%d %d %d %d", &n, &m, &u, &v);
    int x, y;
    for (int i = 1; i <= n; ++i)
      e[i].clear();
    for (int i = 1; i <= m; ++i) {
      scanf("%d %d", &x, &y);
      e[x].push_back(y);
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
      if (i != u && i != v) {
        memset(d, 0, sizeof(d));
        dfs(i, u);
        ans += !d[v];
      }
    printf("%d\n", ans);
  }
} 
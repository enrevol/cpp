#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
#define m2 std::make_pair
 
typedef std::pair<int, int> p2;
 
std::vector<p2> e[10101];
int p[10101][16], h[10101];
long long d[10101];
 
void dfs(int u, int v, int l, int c) {
  p[u][0] = v;
  d[u] = c;
  h[u] = l;
  for (size_t i = 0; i < e[u].size(); ++i) {
    p2 t = e[u][i];
    if (t.first != v)
      dfs(t.first, u, l + 1, d[u] + t.second);
  }
}
 
int lca(int u, int v) {
  if (h[u] < h[v]) std::swap(u, v);
  for (int i = 15; i >= 0; --i)
    if (h[u] - (1 << i) >= h[v])
      u = p[u][i];
  if (u == v) return u;
  assert(h[u] == h[v]);
  for (int i = 15; i >= 0; --i)
    if (p[u][i] != p[v][i]) {
      u = p[u][i];
      v = p[v][i];
    }
  return p[u][0];
}
 
int an(int u, int d) {
  d = h[u] - d;
  for (int i = 15; i >= 0; --i)
    if (h[u] - (1 << i) >= d)
      u = p[u][i];
  return u;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    memset(p, 0, sizeof(p));
    memset(d, 0, sizeof(d));
    memset(h, 0, sizeof(h));
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      e[i].clear();
    int u, v, c;
    for (int i = 1; i < n; ++i) {
      scanf("%d %d %d", &u, &v, &c);
      e[u].push_back(m2(v, c));
      e[v].push_back(m2(u, c));
    }
    dfs(1, 0, 1, 0);
    for (int j = 1; (1 << j) <= n; ++j)
      for (int i = 1; i <= n; ++i)
        p[i][j] = p[p[i][j - 1]][j - 1];
    char s[101];
    while (1) {
      scanf("%s", s);
      if (*s == 'D' && s[1] == 'O') break;
      scanf("%d %d", &u, &v);
      int t = lca(u, v);
      if (*s == 'D') {
        printf("%lld\n", d[u] + d[v] - (d[t] << 1));
      } else {
        scanf("%d", &c);
        --c;
        if (h[u] - h[t] >= c) {
          printf("%d\n", an(u, c));
        } else {
          printf("%d\n", an(v, h[u] + h[v] - (h[t] << 1) - c));
        }
      }
    }
  }
} 
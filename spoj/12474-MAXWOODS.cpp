#include <algorithm>
#include <cstdio>
#include <cstring>
 
char s[222][222];
int g[222][222], n, m;
 
int dfs(const int& x, const int& y, const int& l, const int& r) {
  if (x < 1 || x > n || y < 1 || y > m) return 0;
  if (g[x][y] != -1) return g[x][y];
  if (s[x][y] == 'T') g[x][y] = 1;
  else g[x][y] = 0;
  if (s[x][y] != '#') {
    int val_1 = dfs(x, y - l + r, l, r);
    int val_2 = dfs(x + 1, y, l ^ 1, r ^ 1);
    g[x][y] += std::max(val_1, val_2);
  }
  return g[x][y];
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    memset(g, -1, sizeof(g));
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i)
      scanf("%s", s[i] + 1);
    printf("%d\n", dfs(1, 1, 0, 1));
  }
} 
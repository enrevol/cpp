#include <algorithm>
#include <bitset>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <map>
#include <set>
#include <vector>
 
#define m2 std::make_pair
 
typedef std::pair<int, int> p2;
 
const int dx[] = { 0, -1, 0, 1 };
const int dy[] = { 1, 0, -1, 0 };
 
int a[55][55], g[55][55], n, m;
 
int dfs(const int& x, const int& y) {
  if (g[x][y] != -1)
    return g[x][y];
  int res = 0;  
  for (int i = 0; i < 4; ++i) {
    int xx = x + dx[i];
    int yy = y + dy[i];
    if (1 <= xx && xx <= n && 1 <= yy && yy <= m && a[xx][yy] < a[x][y])
      res += dfs(xx, yy);
  }
  if (res == 0) res = 1;
  g[x][y] = res;
  return res;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  int tt, n_case = 0;
  scanf("%d", &tt);
  while (tt--) {
    memset(g, -1, sizeof(g));
    printf("Case #%d: ", ++n_case);
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
        scanf("%d", a[i] + j);
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
        dfs(i, j);
    int ans = 0;
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j) {
        int f = 1;
        for (int k = 0; k < 4 && f; ++k) {
          int x = i + dx[k];
          int y = j + dy[k];
          if (1 <= x && x <= n && 1 <= y && y <= m && a[x][y] > a[i][j])
            f = 0;
        }
        if (f) ans += g[i][j];
      }
    printf("%d\n", ans);
  }
}
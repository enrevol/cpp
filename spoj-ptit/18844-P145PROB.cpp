#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
 
typedef std::pair<int, int> p2;
 
const int dx[] = { 0, -1, 0, 1 };
const int dy[] = { 1, 0, -1, 0 };
 
std::set<int> h[1010][1010];
int n, m;
int a[1010][1010], sx[2020202], sy[2020202];
 
int dfs(int x, int y, int p, int q) {
  int res = 0;
  sx[1] = x;
  sy[1] = y;
  int sz = 1;
  while (sz) {
    int x = sx[sz];
    int y = sy[sz];
    --sz;
    ++res;
    for (int i = 0; i < 4; ++i) {
      int xx = x + dx[i];
      int yy = y + dy[i];
      if (1 <= xx && xx <= n)
        if (1 <= yy && yy <= m) {
          if (a[xx][yy] == p) {
            if (h[xx][yy].count(q)) continue;
            h[xx][yy].insert(q);
            ++sz;
            sx[sz] = xx;
            sy[sz] = yy;
          }
          if (a[xx][yy] == q) {
            if (h[xx][yy].count(p)) continue;
            h[xx][yy].insert(p);
            ++sz;
            sx[sz] = xx;
            sy[sz] = yy;
          }
        }
    }
  }
  return res;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);  
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      scanf("%d", a[i] + j);
  int ans = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      h[i][j].insert(0);
      int tot = dfs(i, j, a[i][j], 0);
      if (tot > ans)
        ans = tot;
      for (int k = 0; k < 4; ++k) {
        int x = i + dx[k];
        int y = j + dy[k];
        if (1 <= x && x <= n)
          if (1 <= y && y <= m)
            if (a[i][j] != a[x][y])
              if (!h[i][j].count(a[x][y])) {
                h[i][j].insert(a[x][y]);
                int tot = dfs(i, j, a[i][j], a[x][y]);
                if (tot > ans)
                  ans = tot;
              }
      }
    }
  printf("%d", ans);
}  
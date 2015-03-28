#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
char s[55][55];
int dx[55][55], dy[55][55];
 
bool ff(int fx, int fy, int x, int y, int tx, int ty) {
  bool res = true;
  if (fx == x) res &= (dx[x][fy] - dx[x][y]) == (fy - y);
  if (fy == y) res &= (dy[fx][y] - dy[x][y]) == (fx - x);
  if (tx == x) res &= (dx[x][ty] - dx[x][y]) == (ty - y);
  if (ty == y) res &= (dy[tx][y] - dy[x][y]) == (tx - x);
  return res;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%s", s[i] + 1);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      dx[i][j] = dx[i][j - 1] + (s[i][j] == 'B');
  for (int j = 1; j <= m; ++j)
    for (int i = 1; i <= n; ++i)
      dy[i][j] = dy[i - 1][j] + (s[i][j] == 'B');
  bool ans = true;
  for (int i = 1; i <= n && ans; ++i)
    for (int j = 1; j <= m && ans; ++j)
      if (s[i][j] == 'B')
        for (int p = 1; p <= n && ans; ++p)
          for (int q = 1; q <= m && ans; ++q)
            if (s[p][q] == 'B')
              ans &= ff(i, j, i, q, p, q) | ff(i, j, p, j, p, q);
  puts(ans ? "YES" : "NO");
} 
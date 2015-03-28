#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
const int dx[] = { 0, -1, 0, 1 };
const int dy[] = { 1, 0, -1, 0 };
 
char s[111][111];
int a[111][111];
int n, m;
 
void dfs(int x, int y, int k) {
  a[x][y] = k;
  for (int i = 0; i < 4; ++i) {
    int xx = x + dx[i];
    int yy = y + dy[i];
    if (1 <= xx && xx <= n)
      if (1 <= yy && yy <= m)
        if (!a[xx][yy] && s[xx][yy] == '#')
          dfs(xx, yy, k);
  }
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%s", s[i] + 1);
  int ans = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      if (!a[i][j] && s[i][j] == '#')
        dfs(i, j, ++ans);
  printf("%d", ans);
} 
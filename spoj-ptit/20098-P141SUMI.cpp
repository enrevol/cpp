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
 
const int dx[] = { 0, -1, 0, 1 };
const int dy[] = { 1, 0, -1, 0 };
 
bool way[111][111][5];
bool vis[111][111];
 
int nx, ny;
 
void dfs(int x, int y) {
  if (vis[x][y]) return;
  vis[x][y] = 1;
  for (int i = 0; i < 4; ++i) {
    if (way[x][y][i]) continue;
    int xx = x + dx[i];
    int yy = y + dy[i];
    if (1 <= xx && xx <= nx + 1)
      if (1 <= yy && yy <= ny + 1)
        dfs(xx, yy);
  }
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int vx[111];
  int vy[111];  
  int x1[55], y1[55];
  int x2[55], y2[55];
  int n;
  while (scanf("%d", &n)) {
    if (n == 0) break;
    nx = 0;
    ny = 0;
    memset(vis, 0, sizeof(vis));
    memset(way, 0, sizeof(way));   
    for (int i = 1; i <= n; ++i) {
      scanf("%d %d %d %d", x1 + i, y2 + i, x2 + i, y1 + i);
      vx[++nx] = x1[i];
      vx[++nx] = x2[i];
      vy[++ny] = y1[i];
      vy[++ny] = y2[i];  
    }    
    std::sort(vx + 1, vx + nx + 1);
    nx = std::unique(vx + 1, vx + nx + 1) - vx - 1;
    std::sort(vy + 1, vy + ny + 1);
    ny = std::unique(vy + 1, vy + ny + 1) - vy - 1;
    for (int i = 1; i <= n; ++i) {
      x1[i] = std::lower_bound(vx + 1, vx + nx + 1, x1[i]) - vx;
      x2[i] = std::lower_bound(vx + 1, vx + nx + 1, x2[i]) - vx;
      y1[i] = std::lower_bound(vy + 1, vy + ny + 1, y1[i]) - vy;
      y2[i] = std::lower_bound(vy + 1, vy + ny + 1, y2[i]) - vy;
      for (int j = x1[i] + 1; j <= x2[i]; ++j) {
        way[j][y1[i]][0] = way[j][y1[i] + 1][2] = 1;
        way[j][y2[i]][0] = way[j][y2[i] + 1][2] = 1;
      }
      for (int j = y1[i] + 1; j <= y2[i]; ++j) {
        way[x1[i]][j][3] = way[x1[i] + 1][j][1] = 1;
        way[x2[i]][j][3] = way[x2[i] + 1][j][1] = 1;
      }
    }
    int ans = 0;
    for (int i = 1; i <= nx + 1; ++i)
      for (int j = 1; j <= ny + 1; ++j)
        if (!vis[i][j]) {
          dfs(i, j);
          ++ans;
        }
    printf("%d\n", ans);
  }
}
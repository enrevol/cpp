#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
 
const int dx[] = { -1, -2, -2, -1, 1, 2, 2, 1 };
const int dy[] = { 2, 1, -1, -2, -2, -1, 1, 2 };
int g[11][11];
 
int main() {
  //freopen("input.txt", "r", stdin);
  int f_x, f_y, t_x, t_y;
  while (scanf("%d %d %d %d", &f_x, &f_y, &t_x, &t_y) == 4) {
    int g[11][11];
    memset(g, -1, sizeof(g));
    std::queue<std::pair<int, int> > que;
    que.push(std::make_pair(f_x, f_y));
    g[f_x][f_y] = 0;
    while (!que.empty()) {
      std::pair<int, int> t = que.front();
      que.pop();
      for (int i = 0; i < 8; ++i) {
        int x = t.first + dx[i];
        int y = t.second + dy[i];
        if (0 <= x && x < 8 && 0 <= y && y < 8) {
          int val = g[t.first][t.second] + t.first * x + t.second * y;
          if (g[x][y] == -1 || g[x][y] > val) {
            g[x][y] = val;
            que.push(std::make_pair(x, y));
          }
        }
      }
    }
    printf("%d\n", g[t_x][t_y]);
  }
} 
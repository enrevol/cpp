#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
 
const int dx[] = { -1, -2, -2, -1, 1, 2, 2, 1 };
const int dy[] = { 2, 1, -1, -2, -2, -1, 1, 2 };
int g[11][11];
 
int main() {
  //freopen("input.txt", "r", stdin);
  int tt;
  scanf("%d", &tt);
  while (tt--) {    
    char from[11], to[11], g[11][11];
    memset(g, -1, sizeof(g));
    memset(from, 0, sizeof(from));
    memset(to, 0, sizeof(to));
    scanf("%s %s", from + 1, to + 1);
    int from_x = from[1] - 'a' + 1;
    int from_y = 9 - (from[2] - '0');
    int to_x = to[1] - 'a' + 1;
    int to_y = 9 - (to[2] - '0');
    std::queue<std::pair<int, int> > que;
    que.push(std::make_pair(from_x, from_y));
    g[from_x][from_y] = 0;
    while (!que.empty()) {
      std::pair<int, int> t = que.front();
      que.pop();
      for (int i = 0; i < 8; ++i) {
        int x = t.first + dx[i];
        int y = t.second + dy[i];
        if (1 <= x && x <= 8 && 1 <= y && y <= 8) {
          int val = g[t.first][t.second] + 1;
          if (g[x][y] == -1 || g[x][y] > val) {
            g[x][y] = val;
            que.push(std::make_pair(x, y));
          }
        }
      }
    }
    printf("%d\n", g[to_x][to_y]);
  }
} 
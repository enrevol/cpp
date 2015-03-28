#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
 
typedef std::pair<int, int> p2;
 
const int dx[] = { 0, -1, 0, 1 };
const int dy[] = { 1, 0, -1, 0 };
 
char a[101][101];
int b[101][101];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, m;
  scanf("%d %d", &n, &m);
  int x, y;
  for (int i = 1; i <= n; ++i) {
    scanf("%s", a[i] + 1);
    for (int j = 1; j <= m; ++j)
      if (a[i][j] == 'C') {
        x = i;
        y = j;
      }
  }
  memset(b, -1, sizeof(b));
  std::queue<p2> que;
  que.push(p2(x, y));
  b[x][y] = 0;
  while (!que.empty()) {
    p2 t = que.front();
    que.pop();
    for (int i = 0; i < 4; ++i) {
      int xx = t.first + dx[i];
      int yy = t.second + dy[i];
      if (1 <= xx && xx <= n)
        if (1 <= yy && yy <= m)
          if (a[xx][yy] != '*')
            if (b[xx][yy] == -1) {
              b[xx][yy] = b[t.first][t.second] + 1;
              que.push(p2(xx, yy));
            }
    }
  }
  printf("%d", b[1][1]);
} 
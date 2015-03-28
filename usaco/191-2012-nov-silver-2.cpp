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

struct ele {
  int x, y, v;
  ele(int x, int y, int v) : x(x), y(y), v(v) { }
};

char s[33][33];
int dp[33][33];

int main() {
  freopen("distant.in", "r", stdin);
  freopen("distant.out", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, a, b;
  scanf("%d %d %d", &n, &a, &b);
  for (int i = 1; i <= n; ++i)
    scanf("%s", s[i] + 1);
  int ans = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) {
      memset(dp, -1, sizeof(dp));
      dp[i][j] = 0;
      std::queue<ele> que;
      que.push(ele(i, j, 0));
      while (!que.empty()) {
        ele t = que.front();
        que.pop();
        if (t.v != dp[t.x][t.y]) continue;
        for (int k = 0; k < 4; ++k) {
          int x = t.x + dx[k];
          int y = t.y + dy[k];
          if (1 <= x && x <= n)
            if (1 <= y && y <= n) {
              int v = dp[t.x][t.y] + (s[x][y] == s[t.x][t.y] ? a : b);
              if (dp[x][y] == -1 || dp[x][y] > v) {
                dp[x][y] = v;
                que.push(ele(x, y, v));
              }
            }
        }
      }
      for (int p = 1; p <= n; ++p)
        for (int q = 1; q <= n; ++q)
          if (ans < dp[p][q])
            ans = dp[p][q];          
    }
  printf("%d", ans);
}

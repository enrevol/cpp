#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
const int dx[] = { -1, -2, -2, -1 };
const int dy[] = {  2,  1, -1, -2 };
 
int a[101][101], dp[101][101];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      scanf("%d", a[i] + j);
      dp[i][j] = a[i][j];
      int best = 0;
      for (int k = 0; k < 4; ++k) {
        int x = i + dx[k];
        int y = j + dy[k];
        if (1 <= x && 1 <= y && y <= m)
          if (best < dp[x][y]) best = dp[x][y];
      }
      dp[i][j] += best;
    }
  }
  int ans = 0;
  for (int i = 1; i <= m; ++i)
    if (ans < dp[n][i]) ans = dp[n][i];
  printf("%d", ans);
} 
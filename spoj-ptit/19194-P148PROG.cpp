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
 
int dp[33][1010][1010];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, t;
  while (~scanf("%d %d", &n, &t)) {
    if (n | t) {
      memset(dp, 0, sizeof(dp));
      int a;
      int v = -1;
      for (int i = 1; i <= n; ++i) {
        scanf("%d", &a);
        // exclude
        for (int j = 0; j <= t; ++j)
          if (a > t) {
            for (int k = 0; k <= t + 1; ++k)
              dp[i][j][k] += dp[i - 1][j][k];
          } else {
            for (int k = 0; k < a; ++k)
              dp[i][j][k] += dp[i - 1][j][k];
            for (int k = a; k <= t + 1; ++k)
              dp[i][j][a] += dp[i - 1][j][k];
          }        
        // include
        for (int j = 0; j + a <= t; ++j)
          for (int k = 0; k <= t + 1; ++k)
            dp[i][j + a][k] += dp[i - 1][j][k];
        if (a <= t) {
          if (v == -1) {          
            ++dp[i][a][t + 1];
          } else {
            ++dp[i][a][v];
          }
          if (v == -1 || v > a) v = a;
        }
      }
      int ans = 0;
      for (int i = 0; i <= t; ++i)
        for (int j = t + 1 - i; j <= t + 1; ++j)
          ans += dp[n][i][j];
      printf("%d\n", ans);
    }
  }
} 
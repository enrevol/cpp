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
 
const int inf = 0x3c3c3c3c;
 
int a[505];
int pa[505];
int ps[505];
 
int sum[505][505];
int dp[505][505];
 
inline int sqr(int x) {
  return x * x;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, m;
  while (~scanf("%d %d", &n, &m)) {
    if (n == 0 && m == 0) break;
    memset(dp, 0x3c, sizeof(dp));
    for (int i = 1; i <= n; ++i) {
      scanf("%d", a + i);
      pa[i] = pa[i - 1] + a[i];
      ps[i] = ps[i - 1] + sqr(a[i]);
    }
    for (int i = 1; i <= n; ++i)
      for (int j = i + 1; j <= n; ++j)
        sum[i][j] = (sqr(pa[j] - pa[i - 1]) - (ps[j] - ps[i - 1])) >> 1;    
    if (m > 0) {
      for (int i = 2; i <= n; ++i)
        dp[1][i] = sum[1][i - 1];
      for (int j = 1; j < m; ++j)
        for (int i = j + 1; i <= n - (m - j); ++i)
          if (dp[j][i] != inf)
            for (int k = i + 1; k <= n - (m - j - 1); ++k)
              dp[j + 1][k] = std::min(dp[j + 1][k], dp[j][i] + sum[i][k - 1]);
      int ans = inf;
      for (int i = 1; i <= n; ++i)        
        ans = std::min(ans, dp[m][i] + sum[i][n]);
      printf("%d\n", ans);
    } else {
      printf("%d\n", sum[1][n]);
    }
  }
}
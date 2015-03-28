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
 
int a[1010][1010];
int dp[2][1010][1010];
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      scanf("%d", a[i] + j);
  int ans = 0;
  for (int k = 0; k <= 1; ++k)
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
        if (a[i][j] == k) {
          dp[k][i][j] = std::min(dp[k][i - 1][j - 1], std::min(dp[k][i - 1][j], dp[k][i][j - 1])) + 1;
          ans = std::max(ans, dp[k][i][j]);
        }
  printf("%d", ans);
}
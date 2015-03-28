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
 
int a[10101];
int dp[10101][505];
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%d", a + i);
  for (int i = 1; i <= n; ++i) {
    dp[i][0] = dp[i - 1][0];
    for (int j = i - 1; j >= 1 && i - j <= m; --j)
      dp[i][0] = std::max(dp[i][0], dp[j][i - j]);
    for (int j = 1; j <= m; ++j)
      dp[i][j] = dp[i - 1][j - 1] + a[i];
  }
  printf("%d", dp[n][0]);
}
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
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
 
long long dp[22][11][166];
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  for (int i = 1; i <= 20; ++i) {
    for (int j = 0; j <= 10; ++j)
      for (int k = 0; k <= 155; ++k)
        dp[i][j][k] += dp[i - 1][j][k];
    for (int j = 1; j <= 10; ++j)
      for (int k = i; k <= 155; ++k)
        dp[i][j][k] += dp[i - 1][j - 1][k - i];
    ++dp[i][1][i];
  }
  int n, s, k;
  while (~scanf("%d %d %d", &n, &k, &s)) {
    if (n == 0 && s == 0 && k == 0) break;
    printf("%lld\n", dp[n][k][s]);
  }
}
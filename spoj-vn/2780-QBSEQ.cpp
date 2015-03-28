#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
int dp[1010][55];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n, k, a;
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a);
    for (int j = 0; j < k; ++j)
      dp[i][j] = dp[i - 1][j];
    if (dp[i][a % k] == 0) dp[i][a % k] = 1;
    for (int j = 0; j < k; ++j)
      if (dp[i - 1][j])
        if (dp[i][(j + a) % k] < dp[i - 1][j] + 1)
          dp[i][(j + a) % k] = dp[i - 1][j] + 1;
  }
  printf("%d", dp[n][0]);
} 
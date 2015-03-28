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
 
int a[25252];
long long dp[25252][2];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  memset(dp, -1, sizeof(dp));
  int n;
  scanf("%d", &n);
  for (int i = 1; i < n; ++i)
    scanf("%d", a + i);
  if (n == 1) {
    printf("0");
  } else {
    dp[2][1] = a[1];
    for (int i = 3; i <= n; ++i) {
      dp[i][0] = dp[i - 1][1];
      if (dp[i - 2][1] != -1)
        if (dp[i][1] == -1 || dp[i - 2][1] + a[i - 1] < dp[i][1])
          dp[i][1] = dp[i - 2][1] + a[i - 1];
      if (dp[i - 1][1] != -1)
        if (dp[i][1] == -1 || dp[i - 1][1] + a[i - 1] < dp[i][1])
          dp[i][1] = dp[i - 1][1] + a[i - 1];
    }
    printf("%lld", dp[n][1]);
  }
} 
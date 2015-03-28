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

const int mod = 2012;

char s[1010];
int dp[1010][1010];

int main() {
  freopen("bbreeds.in", "r", stdin);
  freopen("bbreeds.out", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  scanf("%s", s + 1);
  int n = strlen(s + 1);
  int x = 1;
  dp[1][0] = dp[1][1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (s[i] == '(') {
      ++x;
      for (int j = 1; j <= x; ++j)
        dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % mod;
      for (int j = 0; j < x; ++j)
        dp[i][j] = (dp[i][j] + dp[i - 1][j]) % mod;
    } else {
      --x;
      for (int j = 0; j <= x; ++j)
        dp[i][j] = (dp[i][j] + dp[i - 1][j + 1] + dp[i - 1][j]) % mod;
    }
  }  
  printf("%d", dp[n][0]);
}

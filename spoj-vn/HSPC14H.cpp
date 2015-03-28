#include <algorithm>
#include <bitset>
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

const int N = 1510;

int cnt[N][N][2], sum[N][N][2], dp[N][N];

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      char s[5];      
      scanf("%s", s);
      int k;
      sscanf(s + 1, "%d", &k);
      cnt[i][j][*s == 'B'] += k;
      sum[i][j][0] = sum[i][j - 1][0] + sum[i - 1][j][0] - sum[i - 1][j - 1][0] + cnt[i][j][0];
      sum[i][j][1] = sum[i][j - 1][1] + sum[i - 1][j][1] - sum[i - 1][j - 1][1] + cnt[i][j][1];
    }
  for (int i = 1; i <= n; ++i) dp[i][1] = 0;
  for (int i = 1; i <= m; ++i) dp[1][i] = 0;
  for (int i = 2; i <= n; ++i)
    for (int j = 2; j <= m; ++j) {
      int x = dp[i - 1][j] + sum[i][j][0] - sum[i - 1][j][0] - cnt[i][j][0];
      int y = dp[i - 1][j - 1] + sum[i][j][0] - sum[i - 1][j][0] + sum[i][j][1] - sum[i][j - 1][1] - cnt[i][j][0] - cnt[i][j][1];
      int z = dp[i][j - 1] + sum[i][j][1] - sum[i][j - 1][1] - cnt[i][j][1];
      dp[i][j] = std::max(x, std::max(y, z));
    }
  printf("%d", dp[n][m]);
}


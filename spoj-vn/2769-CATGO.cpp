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
 
const int N = 55;
 
int a[N], sum[N];
int dp[N][N * N];
int profit[N][N];
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a + i);
    sum[i] = sum[i - 1] + a[i] - 1;
  }
  int m;
  scanf("%d", &m);
  for (int x, y; m--; ) {
    scanf("%d %d", &x, &y);
    if (x < N) profit[x][0] = y;
  }
  for (int i = 1; i < N; ++i)
    for (int j = 1; j < N; ++j)
      for (int k = 1; k < i; ++k)
        profit[i][j] = std::max(profit[i][j], profit[k][j - 1] + profit[i - k][0]);
  for (int i = 1; i <= n; ++i)
    for (int j = 0; j <= sum[i]; ++j)
      for (int k = 0; k <= j && k < N; ++k)
        dp[i][j] = std::max(dp[i][j], dp[i - 1][j - k] + profit[a[i]][k]);
  int ans = 0;
  for (int i = 0; i <= sum[n]; ++i) {
    ans = std::max(ans, dp[n][i] - (i * (i + 1) / 2));
    //printf("cut = %d profit = %d\n", i, dp[n][i]);
  }
  printf("%d", ans);
}
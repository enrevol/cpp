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
 
int k, b;
int arr[33];
int dp[33][33];
long long p[33];
 
int calc(int n) {
  memset(arr, 0, sizeof(arr));
  p[0] = 1;
  int sz = 0;
  while (b * p[sz] <= n)
    p[sz + 1] = b * p[sz], ++sz;
  assert(sz < 33);
  int bt = 0;
  for (int i = sz; i >= 0; --i)
    if (p[i] <= n) {
      arr[i] = 1;
      n -= p[i];
      ++bt;
    }
  int res = 0;
  int cnt = 0;
  for (int i = sz; i >= 0; --i)
    if (arr[i]) {
      int v = k - cnt;      
      if (0 <= v && v <= i)
        res += dp[i][v];
      ++cnt;
    }
  res += bt == k;
  return res;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);  
  for (int i = 0; i <= 30; ++i)
    dp[i][0] = dp[i][i] = 1;
  for (int i = 1; i <= 30; ++i)
    for (int j = 1; j < i; ++j)
      dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
  int x, y;
  scanf("%d %d %d %d", &x, &y, &k, &b);
  printf("%d", calc(y) - calc(x - 1));
}
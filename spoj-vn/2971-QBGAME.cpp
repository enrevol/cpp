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
 
const int N = 10010;
 
int a[N][9];
long long dp[N][257];
int arr[257];
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int sz = 0;
  for (int mask = 0; mask < 256; ++mask) {
    int f = 1;
    for (int i = 0; i < 7 && f; ++i)
      f = ((mask >> i) & 3) != 3;
    if (!f) continue;
    arr[sz++] = mask;
  }
  fprintf(stderr, "sz = %d\n", sz);
  int n;
  int max = -1e9;
  scanf("%d", &n);
  for (int i = 0; i < 8; ++i)
    for (int j = 0; j < n; ++j) {
      scanf("%d", a[j] + i);
      max = std::max(max, a[j][i]);
    }
  if (max < 0) {
    printf("%d", max);
    return 0;
  }
  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < sz; ++j) {      
      int mask = arr[j];
      int nmask = (~mask) & 255;
      long long sum = dp[i][mask];
      for (int k = 0; k < 8; ++k)
        if (mask & (1 << k))
          sum = sum + a[i][k++];
      dp[i + 1][nmask] = std::max(dp[i + 1][nmask], sum);
    }
    for (int mask = 255; mask >= 0; --mask)
      for (int j = 0; j < 8; ++j)
        if (mask & (1 << j)) {
          int nmask = mask ^ (1 << j);
          dp[i + 1][nmask] = std::max(dp[i + 1][nmask], dp[i + 1][mask]);
        }    
  }
  long long ans = -1;
  for (int i = 0; i < sz; ++i) {
    int mask = arr[i];
    long long sum = dp[n - 1][mask];
    for (int i = 0; i < 8; ++i)
      if (mask & (1 << i))
        sum = sum + a[n - 1][i];
    ans = std::max(ans, sum);
  }
  printf("%lld", ans);
}
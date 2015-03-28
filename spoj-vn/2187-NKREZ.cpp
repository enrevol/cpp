#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
struct ss {
  int f, t;
  bool operator< (const ss& a) const {
    return t < a.t;
  }
} a[10101];
 
int dp[10101];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d %d", &a[i].f, &a[i].t);
  std::sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; ++i) {
    int lo = 1;
    int hi = i - 1;
    int p = -1;
    while (lo <= hi) {
      int mi = (lo + hi) >> 1;
      if (a[mi].t <= a[i].f) {
        p = mi;
        lo = mi + 1;        
      } else {
        hi = mi - 1;
      }
    }
    dp[i] = a[i].t - a[i].f;
    if (p != -1)
      dp[i] += dp[p];
    if (dp[i - 1] > dp[i])
      dp[i] = dp[i - 1];
  }
  printf("%d", dp[n]);
} 
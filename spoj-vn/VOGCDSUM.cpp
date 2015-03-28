#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
const int mod = 1e9 + 7;
 
long long a[101010];
long long dp[101010][18];
int n;
 
inline long long query(int f, int t) {
  int k = std::__lg(t - f + 1);
  return std::__gcd(dp[f][k], dp[t - (1 << k) + 1][k]);
}
 
int ff(long long val, int i, int pos) {
  int lo = pos + 1;
  int hi = n;
  int res = n + 1;
  while (lo <= hi) {
    int mi = (lo + hi) >> 1;
    if (query(i, mi) == val) {
      lo = mi + 1;
    } else {
      hi = mi - 1;
      res = mi;
    }
  }
  return res;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", a + i);
    dp[i][0] = a[i];
  }
  for (int j = 1; 1 << j <= n; ++j)
    for (int i = 1; i + (1 << j) - 1 <= n; ++i)
      dp[i][j] = std::__gcd(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
  long long ans = 0;
  for (int i = 1; i <= n; ++i) {
    int p = i;
    while (p <= n) {      
      long long val = query(i, p);
      int k = p;
      p = ff(val, i, p);
      ans += val * (p - k);
      ans %= mod;
    }
  }
  printf("%lld", ans);
} 
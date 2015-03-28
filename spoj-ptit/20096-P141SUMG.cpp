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
 
const int N = 1e5;
 
bool dig[11];
long long x, a, b;
long long dp[12][N + 5];
 
long long solve(long long p, int n) {  
  long long f = p;
  long long t = p;
  for (int i = 0; i < n; ++i) {
    f = f * 10;
    t = t * 10 + 9;
  }
  //fprintf(stderr, "p = %lld n = %d -> %lld -> %lld\n", p, n, f, t);
  if (b < f || t < a) return 0;
  if (n == 0) return p % x == 0;
  bool mem = a <= f && t <= b;
  long long& ref = dp[n][p % x];
  if (mem && ref >= 0) return ref;
  long long res = 0;  
  for (int i = 0; i <= 9; ++i)
    if (dig[i] || (i == 0 && p == 0))
      res += solve(p * 10 + i, n - 1);
  if (mem) ref = res;
  return res;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);  
  scanf("%lld %lld %lld", &x, &a, &b);
  char s[15];
  scanf("%s", s);
  for (int i = 0; s[i]; ++i)
    dig[s[i] - '0'] = 1;
  if (x >= N) {
    int ans = 0;
    int k = 0;
    for (long long i = x; i <= b; i += x) {
      if (i < a) continue;
      bool f = 1;
      for (long long t = i; t && f; t /= 10)
        f = dig[t % 10];
      ans += f;
    }
    printf("%d", ans);
  } else {
    memset(dp, -1, sizeof(dp));
    long long ans = solve(0, 11);
    printf("%lld", ans);
  }
}
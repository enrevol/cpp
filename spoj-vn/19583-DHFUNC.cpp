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
 
typedef unsigned long long ull;
 
ull a, b, mod;
ull fi[1010];
ull dp[1010][1010];
 
inline void sh(ull& x, int s) {  
  while (s--) {
    x <<= 1;
    while (x >= mod) x -= mod;
  }
}
 
ull multi(const ull& x, const ull& y) {
  ull xl = x >> 32, xr = x & ((1ull << 32) - 1);
  ull yl = y >> 32, yr = y & ((1ull << 32) - 1);
  ull v1 = (xl * yl) % mod;
  ull v2 = (((xl * yr) % mod) + ((xr * yl) % mod)) % mod;
  ull v3 = (xr * yr) % mod;
  sh(v1, 64);
  sh(v2, 32);
  return (v1 + v2 + v3) % mod;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output2.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  fi[1] = fi[2] = 1;
  for (int i = 1; i <= 1000; ++i)
    dp[i][0] = dp[0][i] = i;
  int tt;
  for (std::cin >> tt; tt--; ) {
    int x, y;
    std::cin >> x >> y >> a >> b >> mod;
    a %= mod;
    b %= mod;
    for (int i = 3; i <= 1000; ++i)
      fi[i] = (fi[i - 1] + fi[i - 2]) % mod;
    for (int i = 1; i <= x; ++i)
      for (int j = 1; j <= y; ++j)
        dp[i][j] = (multi(a, dp[i - 1][j]) + multi(b, dp[i][j - 1]) + fi[std::__gcd(i, j)]) % mod;
    std::cout << dp[x][y] % mod << '\n';
  }
}
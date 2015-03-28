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
 
#define DEBUG(z, x) { cerr << setw(z) << "" << (#x) << " = " << (x) << '\n'; }
 
using namespace std;

int z[40], dp[3][1 << 14 | 1];
 
inline int pmod(long long b, int mod) {
  return 1LL * dp[0][b & 16383] * dp[1][(b >> 14) & 8191] % mod * dp[2][b >> 27] % mod;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, mod;
  long long x, a, b, c, d;
  cin >> n >> x >> a >> b >> c >> d >> mod;
  x %= mod;  
  z[0] = x;
  for (int i = 1; i < 40; ++i) {
    z[i] = 1LL * z[i - 1] * z[i - 1] % mod;
  }
  dp[0][0] = dp[1][0] = dp[2][0] = 1;
  for (int mask = 1; mask < 1 << 14; ++mask) {
    int v = mask & -mask;
    dp[0][mask] = 1LL * dp[0][mask - v] * z[__builtin_ctz(v)] % mod;
  }
  for (int mask = 1; mask < 1 << 13; ++mask) {
    int v = mask & -mask;
    dp[1][mask] = 1LL * dp[1][mask - v] * z[14 + __builtin_ctz(v)] % mod;
    dp[2][mask] = 1LL * dp[2][mask - v] * z[27 + __builtin_ctz(v)] % mod;
  }  
  long long ans = 0;
  for (int i = 1; i <= n; ++i) {
    ans += pmod(a, mod);
    a = (a * b + c) % d;
  }
  cout << ans % mod;
}

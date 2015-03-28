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

long long n;
long long dp[17][3], p[17];

long long calc(long long prefix, int prev, int digit) {
  long long f = prefix * p[digit];
  if (n < f) return 0;
  if (digit == 0) return 1;
  long long t = f + p[digit] - 1;
  if (t <= n && dp[digit][prev] != -1) {
    return dp[digit][prev];
  }  
  long long r = 0;
  prefix = (prefix << 3) + (prefix << 1);
  for (int i = 0; i <= 9; ++i, ++prefix) {
    if (!prev || i != 3) {
      r += calc(prefix, i == 1, digit - 1);
    }
  }
  if (t <= n) {
    dp[digit][prev] = r;
  }
  return r;
}

long long calc(long long x) {
  long long r = 0;
  if (r >= 0) {
    ++r;
    n = x;    
    for (int dig = 0; dig <= 9; ++dig) {
      r += calc(dig, dig == 1, 15);
    }
  }
  return r;
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  p[0] = 1;
  for (int i = 1; i < 17; ++i) {
    p[i] = p[i - 1] * 10;
  }
  memset(dp, -1, sizeof(dp));
  long long f, t;
  while (std::cin >> f >> t) {
    std::cout << calc(t) - calc(f - 1) << '\n';
  }
}

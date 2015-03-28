#include <algorithm>
#include <bitset>
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
 
ull a[1010];
ull b[1010];
int dp[2][1010];
std::bitset<1100005> sieve;
 
inline bool pr(const int& x) {
  if (x & 1) return !sieve[x >> 1];
  return x == 2;
}
 
inline bool ok(const ull& x) {
  bool e = 0;
  bool f = 0;
  {
    ull lo = 1;
    ull hi = 33e8;    
    while (lo <= hi) {
      ull mi = (lo + hi) >> 1;
      if (mi * mi > x) {
        hi = mi - 1;
      } else if (mi * mi < x) {
        lo = mi + 1;
      } else {
        e = 1;
        break;
      }
    }
  }
  {
    ull lo = 1;
    ull hi = 23e5;
    while (lo <= hi) {
      ull mi = (lo + hi) >> 1;
      if (mi * mi * mi > x) {
        hi = mi - 1;        
      } else if (mi * mi * mi < x) {
        lo = mi + 1;
      } else {
        f = pr(mi);
        break;
      }
    }
  }
  return (e || f) && !(e && f);
}
 
inline void input(ull arr[], int& sz) {
  std::string line;
  std::getline(std::cin, line);
  std::stringstream ss(line);
  while (ss) ss >> arr[++sz];
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  sieve[0] = 1;
  for (int i = 3; i * i < 2200000; i += 2)
    if (!sieve[i >> 1])
      for (int j = i * i; j < 2200000; j += i << 1)
        sieve[j >> 1] = 1;
  int na = 0;
  int nb = 0;
  input(a, na);
  input(b, nb);
  --na;
  --nb;
  bool e = 0, f = 1;
  for (int i = 1; i <= na; ++i, e ^= 1, f ^= 1) {
    if (ok(a[i])) {
      for (int j = 1; j <= nb; ++j) {
        if (b[j] == a[i]) {
          dp[f][j] = dp[e][j - 1] + 1;
        } else {
          dp[f][j] = std::max(dp[e][j], dp[f][j - 1]);
        }
      }
    } else {      
      for (int j = 1; j <= nb; ++j)
        dp[f][j] = std::max(dp[e][j], dp[f][j - 1]);
    }
  }
  std::cout << dp[na & 1][nb];
}
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

typedef unsigned long long uint64_t;

bool vis[20][170];
uint64_t dp[20][170], p[20];

uint64_t calc(uint64_t qf, uint64_t qt, uint64_t prefix, int digit, int sum) {    
  uint64_t f = prefix * p[digit];
  uint64_t t = f + p[digit] - 1;
  if (t < qf || qt < f) return 0;
  if (sum == 0) return qf <= f && f <= qt;
  if (digit == 0) return sum == 0;
  if (qf <= f && t <= qt)
    if (vis[digit][sum])
      return dp[digit][sum];
  uint64_t r = 0;
  for (int i = 0; i <= 9; ++i) {
    if (i <= sum) {
      r += calc(qf, qt, prefix * 10 + i, digit - 1, sum - i);
    }
  }
  if (qf <= f && t <= qt) {
    vis[digit][sum] = 1;
    dp[digit][sum] = r;
  }
  return r;
}

uint64_t calc(uint64_t f, uint64_t t) {
  memset(vis, 0, sizeof(vis));
  uint64_t r = 0;
  for (int digit = 1; digit <= 19; ++digit) {
    for (int sum = 1; sum <= 9 * digit; ++sum) {
      uint64_t qf = (f - 1) / sum + 1;
      uint64_t qt = t / sum;
      if (qf <= qt) {
        for (int num = 1; num <= 9; ++num) {
          if (num <= sum) {
            r += calc(qf, qt, num, digit - 1, sum - num);
          }  
        }        
      }
    }
  }
  return r;
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  p[0] = 1;
  for (int i = 1; i < 20; ++i) {
    p[i] = p[i - 1] * 10;
  }
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    uint64_t f, t;
    scanf("%llu %llu", &f, &t);
    printf("%llu\n", calc(f, t));
  }
}

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

const int N = 20;

int k;
int dp[1 << N], a[N], q[1 << N];

inline void check(int mask) {
  if (mask == k) {
//    fprintf(stderr, "mask = %d\n", mask);
    printf("%d", dp[mask] - 1);
    exit(0);
  }
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d %d", &n, &k);
  k = 1 << (k - 1);
  for (int i = 0; i < n; ++i) {
    int x;
    scanf("%d", &x);
    int mask = 0;
    while (x--) {
      int v;
      scanf("%d", &v);
      mask |= 1 << (v - 1);
    }
    a[i] = ~mask;
//    fprintf(stderr, "i = %d mask = %d\n", i, mask);
  }
  int fmask = 0;
  for (int i = 0; i < n; ++i) {
    int v;
    scanf("%d", &v);
    fmask |= v << i;
  }
//  fprintf(stderr, "fmask = %d\n", fmask);
  dp[fmask] = 1;
  check(fmask);
  int qsz = 0;
  q[qsz++] = fmask;
  for (int qi = 0; qi < qsz; ++qi) {
    int mask = q[qi];
    for (int i = 0; i < n; ++i) {
      int nmask = (mask & a[i]) | (1 << i);
      if (!dp[nmask]) {
        dp[nmask] = dp[mask] + 1;
        check(nmask);
        q[qsz++] = nmask;
      }
    }
  }
  puts("-1");
}

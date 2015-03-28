#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n;
  scanf("%d", &n);
  int nn = n;
  --nn;
  nn |= nn >> 1;
  nn |= nn >> 2;
  nn |= nn >> 4;
  nn |= nn >> 8;
  nn |= nn >> 16;
  ++nn;
  int step = 0;
  if (n < nn) {
    int lo = 1, hi = nn - 1;
    while (lo <= hi) {
      ++step;
      int mi = (lo + hi) >> 1;
      if (mi == n) break;
      if (n < mi) hi = mi - 1;
      if (n > mi) lo = mi + 1;
    }
  }
  printf("%d %d", nn, step);
} 
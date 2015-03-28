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

int a[101010];
int b[101010];

const double eps = 1e-5;

inline bool eq(const double& a, const double& b) {
  return fabs(a - b) <= eps;
}

int main() {
  assert(freopen("sabotage.in", "r", stdin));
  assert(freopen("sabotage.out", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a + i);
    b[i] = b[i - 1] + a[i];
  }
  double lo = 1;
  double hi = 1e4;
  double ans = 1e4;
  while (lo < hi && !eq(lo, hi)) {
    double mi = (lo + hi) / 2;
    bool f = false;
    double best = b[1];
    for (int i = 2; i < n && !f; ++i) {
      double t = b[i - 1] - mi * (i - 1);
      if (best > t) best = t;
      double v = (b[n] - mi * n) - (b[i] - mi * i);
      f = eq(v + best, 0) || (v + best) < 0;
    }
    if (f) {
      ans = mi;
      hi = mi;
    } else {
      lo = mi;
    }
  }
  printf("%.3lf", ans);
}

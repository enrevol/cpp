#include <algorithm>
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
 
const int N = 100010;
 
struct point {
  int x, y;
  bool operator<(const point& p) const {
    if (x != p.x) return x < p.x;
    return y < p.y;
  }
} p[N], h[N << 1];
 
// angle: abc
// vector: ab * ac
inline long long cross(const point& a, const point& b, const point& c) {
  return 1ll * (a.x - b.x) * (c.y - b.y) - 1ll * (a.y - b.y) * (c.x - b.x);
}
 
inline long long sqr(int x) {
  return 1ll * x * x;
}
 
inline long long dist(const point& a, const point& b) {
  return sqr(a.x - b.x) + sqr(a.y - b.y);
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int tt;
  for (scanf("%d", &tt); tt--; ) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
      scanf("%d %d", &p[i].x, &p[i].y);
    }
    std::sort(p + 1, p + n + 1);
    int sz = 0;
    for (int i = 1; i <= n; ++i) {
      while (sz >= 2 && cross(h[sz - 1], h[sz], p[i]) >= 0)
        --sz;
      h[++sz] = p[i];
    }
    for (int i = n - 1, t = sz; i >= 1; --i) {
      while (sz > t && cross(h[sz - 1], h[sz], p[i]) >= 0)
        --sz;
      if (i > 1) h[++sz] = p[i];
    }
    std::copy(h + 1, h + sz + 1, h + sz + 1);
    long long ans = 0;
    for (int i = 1, j = 2; i <= sz; ++i) {
      while (j < (sz << 1) && dist(h[i], h[j]) < dist(h[i], h[j + 1]))
        ++j;
      long long d = dist(h[j], h[i]);
      if (d > ans) ans = d;
    }
    printf("%lld\n", ans);
  }
}
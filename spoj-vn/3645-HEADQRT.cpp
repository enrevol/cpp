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
  bool operator<(const point& a) const {
    if (x != a.x) return x < a.x;
    return y < a.y;
  }
} pa[N], pb[N], ha[N], hb[N];
 
inline bool cross(const point& a, const point& b, const point& c) {
  return 1ll * (a.x - b.x) * (c.y - b.y) - 1ll * (a.y - b.y) * (c.x - b.x) >= 0;
}
 
void convex(int n, point p[], int& sz, point h[]) {
  std::sort(p + 1, p + n + 1);
  for (int i = 1; i <= n; ++i) {
    while (sz >= 2 && cross(h[sz - 1], h[sz], p[i]))
      --sz;
    h[++sz] = p[i];
  }
  for (int i = n - 1, t = sz; i >= 1; --i) {
    while (sz > t && cross(h[sz - 1], h[sz], p[i]))
      --sz;
    if (i > 1) h[++sz] = p[i];
  }
}
 
inline int next(int x, int n) {
  if (x < n) return x + 1;
  return 1;
}
 
inline int pred(int x, int n) {
  if (x > 1) return x - 1;
  return n;
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
    int na = 0;
    int nb = 0;
    for (int i = 1; i <= n; ++i) {
      int x, y, c;
      scanf("%d %d %d", &x, &y, &c);
      if (c == 0) {
        ++na;
        pa[na].x = x;
        pa[na].y = y;
      } else {
        ++nb;
        pb[nb].x = x;
        pb[nb].y = y;
      }
    }
    int sa = 0;
    int sb = 0;
    convex(na, pa, sa, ha);
    convex(nb, pb, sb, hb);
    long long best = 0;
    for (int i = 1, j = 1; i <= sa; ++i) {
      while (dist(ha[i], hb[j]) < dist(ha[i], hb[next(j, sb)])) j = next(j, sb);
      while (dist(ha[i], hb[j]) < dist(ha[i], hb[pred(j, sb)])) j = pred(j, sb);
      long long d = dist(ha[i], hb[j]);
      if (d > best) best = d;
    }
    long long x = sqrt(best);
    assert(sqr(x) <= best);
    while (sqr(x + 1) <= best) ++x;
    printf("%lld\n", x);
  }
}
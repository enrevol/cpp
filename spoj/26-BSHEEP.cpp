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
 
typedef std::pair<int, int> p2;
 
const int mx = 1e5;
 
struct sheep {
  int x, y, i;
} sh[mx + 10], st[mx + 10];
 
bool ff(const sheep& a, const sheep& b) {
  if (a.y != b.y) return a.y < b.y;
  if (a.x != b.x) return a.x < b.x;
  return a.i < b.i;
}
 
bool ee(const sheep& a, const sheep& b) {
  return a.x == b.x && a.y == b.y;
}
 
inline int part(int x, int y) {
  if (x > 0 && y >= 0) return 1;
  if (x <= 0 && y > 0) return 2;
  if (x < 0 && y <= 0) return 3;
  return 4;
}
 
bool cmp(const sheep& a, const sheep& b) {
  int ax = a.x - sh[1].x;
  int ay = a.y - sh[1].y;
  int bx = b.x - sh[1].x;
  int by = b.y - sh[1].y;
  int ap = part(ax, ay);
  int bp = part(bx, by);
  if (ap != bp) return ap < bp;
  // ay / ax < by / bx;
  return 1ll * ay * bx < 1ll * ax * by;
}
 
// ba * bc
inline bool cross(const sheep& a, const sheep& b, const sheep& c) {
  int ax = a.x - b.x;
  int ay = a.y - b.y;
  int cx = c.x - b.x;
  int cy = c.y - b.y;
  return 1ll * ax * cy - 1ll * ay * cx >= 0;
}
 
inline double sqr(double x) {
  return x * x;
}
 
double dist(const sheep& a, const sheep& b) {
  return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
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
      scanf("%d %d", &sh[i].x, &sh[i].y);
      sh[i].i = i;
    }
    std::sort(sh + 1, sh + n + 1, ff);
    n = std::unique(sh + 1, sh + n + 1, ee) - sh - 1;
    if (n == 1) {      
      puts("0.00");
      puts("1");
      putchar('\n');
      continue;
    }
    std::sort(sh + 2, sh + n + 1, cmp);
    int sz = 0;
    for (int i = 1; i <= n; ++i) {
      while (sz >= 2 && cross(st[sz - 1], st[sz], sh[i]))
        --sz;
      st[++sz] = sh[i];
    }
    double ans = dist(st[sz], st[1]);
    for (int i = 1; i < sz; ++i)
      ans += dist(st[i], st[i + 1]);
    printf("%.2lf\n", ans);
    for (int i = 1; i <= sz; ++i)
      printf("%d ", st[i].i);
    putchar('\n');
    putchar('\n');
  }
}
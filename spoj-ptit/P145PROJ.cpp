#include <algorithm>
#include <cassert>
#include <complex>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
typedef std::pair<int, int> p2;
 
struct ss {
  int x, y;
} p[1515], q[1515];
 
inline int part(int x, int y) {
  if (x > 0 && y >= 0) return 1;
  if (x <= 0 && y > 0) return 2;
  if (x < 0 && y <= 0) return 3;
  return 4;
}
 
bool ff(ss a, ss b) {
  int ap = part(a.x, a.y);
  int bp = part(b.x, b.y);
  if (ap == bp) return 1ll * a.y * b.x < 1ll * a.x * b.y;
  return ap < bp;
}
 
int n;
 
inline bool ccw(const ss& a, const ss& b) {
  return (-1ll * a.x * (b.y - a.y) + 1ll * a.y * (b.x - a.x)) <= 0;
}
 
int num(int k) {
  if (k > n) return k - n + 1;
  return k;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);4
  //std::cin.tie(0);
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d %d", &p[i].x, &p[i].y);
  long long cnt = 0;
  for (int i = 1; i <= n; ++i) {
    std::copy(p + 1, p + n + 1, q + 1);
    std::swap(q[i], q[1]);
    for (int j = 2; j <= n; ++j) {
      q[j].x -= q[1].x;
      q[j].y -= q[1].y;
    }
    std::sort(q + 2, q + n + 1, ff);
    int k = 2;
    for (int j = 2; j <= n; ++j) {
      if (k < j) k = j;
      while (num(k + 1) != j && ccw(q[j], q[num(k + 1)]))
        ++k;
      int tot = k - j + 1;
      cnt += ((tot - 1) * (tot - 2)) >> 1;
    }
  }
  cnt -= 1ll * n * (n - 1) * (n - 2) * (n - 3) / 12;
  double ans = 1.f * cnt / (1ll * n * (n - 1) * (n - 2) / 6);
  printf("%.16lf", ans + 3);
} 
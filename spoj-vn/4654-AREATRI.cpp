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
 
const int N = 1010;
 
struct point {
  int x, y;
} p[N], tmp[N << 1];
 
inline int partition(int x, int y) {
  if (x > 0 && y >= 0) return 0;
  if (x <= 0 && y > 0) return 1;
  if (x < 0 && y <= 0) return 2;
  return 3;
}
 
bool cmp(const point& a, const point& b) {
  int ax = a.x - tmp[0].x, ay = a.y - tmp[0].y;
  int bx = b.x - tmp[0].x, by = b.y - tmp[0].y;
  int ap = partition(ax, ay);
  int bp = partition(bx, by);
  if (ap != bp) return ap < bp;
  // ay / ax < by / bx
  return ay * bx < ax * by;
}
 
// ba * bc
inline int ccw(const point& a, const point& b, const point& c) {
  return (a.x - b.x) * (c.y - b.y) - (a.y - b.y) * (c.x - b.x);
}
 
int sumx[N << 1];
int sumy[N << 1];
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%d %d", &p[i].x, &p[i].y);
  long long ans = 0;
  for (int i = 0; i < n; ++i) {
    std::copy(p, p + n, tmp);
    std::swap(tmp[0], tmp[i]);
    std::sort(tmp + i + 1, tmp + n, cmp);
    std::copy(tmp + i + 1, tmp + n, tmp + n);
    int m = n + (n - i - 2);
    for (int j = 1; j <= m; ++j) {
      sumx[j] = sumx[j - 1] + tmp[j].x;
      sumy[j] = sumy[j - 1] + tmp[j].y;
    }
    for (int j = i + 1, k = j; j < n; ++j) {
      if (k < j) k = j;
      while (k + 1 <= m && ccw(tmp[j], tmp[0], tmp[k + 1]) >= 0) ++k;
      if (j == k) continue;
      int vx = sumx[k] - sumx[j];
      int vy = sumy[k] - sumy[j];
      int cnt = k - j;
      ans = ans + 1ll * tmp[0].x * tmp[j].y * cnt
                + 1ll * tmp[j].x * vy
                + 1ll * vx * tmp[0].y
                - 1ll * tmp[0].x * vy
                - 1ll * tmp[j].x * tmp[0].y * cnt
                - 1ll * vx * tmp[j].y;
    }
    //fprintf(stderr, "ans = %lld\n", ans);
  }  
  printf("%.1lf", ans * 0.5);
}
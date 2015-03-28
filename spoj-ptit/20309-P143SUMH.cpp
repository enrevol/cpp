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
 
typedef long double ld;
 
const int N = 10010;
const ld PI = 3.14159265358979323846264338327950288;
const ld EPS = 1e-12;
 
int x[N], y[N];
 
inline bool eq(ld x, ld y) {
  return fabs(x - y) <= EPS * fabs(x);
}
 
inline ld sqr(ld x) {
  return x * x;
}
 
inline ld dist(ld x1, ld y1, ld x2, ld y2) {
  return sqrt(sqr(x1 - x2) + sqr(y1 - y2));
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int tt;
  for (scanf("%d", &tt); tt--; ) {
    int r, n;
    scanf("%d %d", &r, &n);
    assert(r > 0 && n > 2);
    for (int i = 0; i < n; ++i)
      scanf("%d %d", x + i, y + i);
    x[n] = x[0];
    y[n] = y[0];
    ld peri = 0;
    for (int i = 0; i < n; ++i)
      peri += dist(x[i], y[i], x[i + 1], y[i + 1]);
    //fprintf(stderr, "peri = %lf\n", double(peri));
    ld arc = PI * (r << 1);
    if (eq(arc, peri) || arc > peri) {
      puts("Not possible");
    } else {
      for (ld f = 1e-10, t = 1; f < t && !eq(f, t); ) {
        ld m = (f + t) * 0.5;
        ld val = peri * m + arc;
        if (eq(val, peri)) {
          printf("%.15lf\n", double(m));
          break;
        } else {
          if (val > peri) {
            t = m;
          } else {
            f = m;
          }
        }
      }
    }
  }
}
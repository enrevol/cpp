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
 
const int w = 1e3;
 
int h[101010];
 
struct node {
  int cnt;
  double area;
  double a, b, c;
} fw[1010];
 
inline double query(int x) {
  int cnt = 0;
  double area = 0;
  double a = 0, b = 0, c = 0;
  for (int i = x; i; i -= i & -i) {
    cnt += fw[i].cnt;
    area += fw[i].area;
    a += fw[i].a;
    b += fw[i].b;
    c += fw[i].c;
  }
  return cnt * x + area + a * x * x + b * x + c;
}
 
inline void update(int x, int y, int v) {
  int f = std::min(x, y);
  int t = std::max(x, y);
  for (int i = 1; i <= w; i += i & -i)
    fw[i].cnt += v;
  for (int i = f + 1; i <= w; i += i & -i)
    fw[i].cnt -= v;
  double vx = v * (f + t) * 0.5;
  for (int i = t + 1; i <= w; i += i & -i)
    fw[i].area += vx;
  if (f < t) {
    double va = v * 0.5 / (t - f);
    double vb = v * 1.0 * t / (t - f);
    double vc = v * 0.5 * f * f / (t - f);
    for (int i = f + 1; i <= w; i += i & -i) {
      fw[i].a -= va;
      fw[i].b += vb;
      fw[i].c -= vc;
    }
    for (int i = t + 1; i <= w; i += i & -i) {
      fw[i].a += va;
      fw[i].b -= vb;
      fw[i].c += vc;
    }
  }
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%d", h + i);
  for (int i = 1; i < n; ++i)
    update(h[i], h[i + 1], 1);
  char s[5];
  int x, y;
  while (m--) {
    scanf("%s %d", s, &x);
    if (*s == 'Q') {
      double val = x == 0 ? 0 : query(x);
      double tot = x * (n - 1);
      printf("%.3lf\n", tot - val);
    } else {
      scanf("%d", &y);
      ++x;
      if (x > 1) update(h[x], h[x - 1], -1), update(y, h[x - 1], 1);
      if (x < n) update(h[x], h[x + 1], -1), update(y, h[x + 1], 1);
      h[x] = y;
    }
  }
}
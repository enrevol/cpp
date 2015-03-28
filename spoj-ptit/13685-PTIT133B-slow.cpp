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
 
const int w = 1000;
 
int h[101010];
 
struct node {
  int cnt;
  double area;
  double a, b, c;
  node() { }
  node(int cnt, double area, double a, double b, double c) : cnt(cnt), area(area), a(a), b(b), c(c) { }
  node operator+ (const node& x) const {
    return node(cnt + x.cnt, area + x.area, a + x.a, b + x.b, c + x.c);
  }
  node operator- (const node& x) const {
    return node(cnt - x.cnt, area - x.area, a - x.a, b - x.b, c - x.c);
  }
} fw[w + 10][w + 10];
 
// hb >= ha
// x = (hb - h) / (hb - ha)
// x + 1 = (hb - h + hb - ha) / (hb - ha)
// s = ha + (x + 1) * (h - ha) / 2
//   = ha + (2 * hb - h - ha) / (hb - ha) * (h - ha) / 2
//   = ha + (2 * hb - h - ha) * (h - ha) / ((hb - ha) * 2)
// ts = ha * (hb - ha) * 2 + (2 * hb - h - ha) * (h - ha)
//    = ha * hb * 2 - ha * ha * 2 + 2 * hb * h - 2 * hb * ha - h * h + h * ha - ha * h + ha * ha
//    = 2ab - 2aa + 2bh - 2ab - hh + ah - ah + aa
// A = -1
// B = 2 * hb + ha - ha = 2 * hb
// C = ha * hb * 2 - ha * ha * 2 - 2 * hb * ha + ha * ha = 2ab - 2aa - 2ab + aa = -ha * ha
// ms = (hb - ha) * 2
 
// x >= y
void update(int x, int y, int v) {
  double f = v * (x + y) * .5;
  double a = v * 0.5 / (x - y);
  double b = v * 1.0 * x / (x - y);
  double c = v * 0.5 * y * y / (x - y);
  for (int i = x + 1; i <= w + 1; i += i & -i)
    for (int j = y + 1; j <= w + 1; j += j & -j) {
      fw[i][j].cnt += v;
      fw[i][j].area += f;
      if (x > y) {
        fw[i][j].a -= a;
        fw[i][j].b += b;
        fw[i][j].c -= c;
      }
    }
}
 
node query(int x, int y) {
  node res(0, 0, 0, 0, 0);
  for (int i = x + 1; i; i -= i & -i)
    for (int j = y + 1; j; j -= j & -j)
      res = res + fw[i][j];
  return res;
}
 
double calc(int x) {
  // area : (1 -> x, 1 -> x)
  node xarea = query(x, x);
  // cnt : (x+1 -> w, x+1 -> w)
  // + (1 -> w, 1 -> w)
  // + (1 -> x, 1 -> x)
  // - (1 -> x, 1 -> w)
  // - (1 -> w, 1 -> x)
  node xcnt = query(w, w) + query(x, x) - query(x, w) - query(w, x);
  // coef : (1 -> x, x+1 -> w) + (x+1 -> w, 1 -> x)
  // + (1 -> x, 1 -> w)
  // + (1 -> w, 1 -> x)
  // - (1 -> x, 1 -> x) x2
  node xcoef = query(x, w) + query(w, x) - query(x, x) - query(x, x);
  return (xarea.area) + (x * xcnt.cnt) + (x * x * xcoef.a + x * xcoef.b + xcoef.c);
}
 
void upseg(int x, int y, int v) {
  int p = std::max(x, y);
  int q = std::min(x, y);
  update(p, q, v);
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
    upseg(h[i], h[i + 1], 1);
  char s[5];
  int x, y;
  while (m--) {
    scanf("%s %d", s, &x);
    if (*s == 'Q') {
      double val = calc(x);
      double tot = x * (n - 1);
      printf("%.3lf\n", tot - val); 
    } else {
      scanf("%d", &y);
      ++x;
      if (x > 1) upseg(h[x], h[x - 1], -1), upseg(y, h[x - 1], 1);
      if (x < n) upseg(h[x], h[x + 1], -1), upseg(y, h[x + 1], 1);
      h[x] = y;
    }
  }
}
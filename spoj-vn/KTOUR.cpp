#include <algorithm>
#include <bitset>
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
  point(int x = 0, int y = 0) : x(x), y(y) { }  
  inline friend bool operator<(const point& a, const point& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
  }
  inline friend bool operator==(const point& a, const point& b) {
    return a.x == b.x;
  }
  inline friend point mid(const point& a, const point& b) {    
    return point((a.x + b.x) >> 1, (a.y + b.y) >> 1);
  }
} f[N], t[N];

int y, stack[N];

struct line {
  int a, b;
  long long c;
  // ax + by = c
  line(const point& p, const point& q) {
    a = q.y - p.y;
    b = p.x - q.x;
    c = 1LL * a * p.x + 1LL * b * p.y;
  }
  line (int a, int b, const point& p) : a(a), b(b) {
    c = 1LL * a * p.x + 1LL * b * p.y;
  }
  inline double get() const {
    return 1.0 * (c - b * y) / a;
  }
};

int check(const point& a, const point& b, const point& c) {
  point m_ab = mid(a, b);
  point m_bc = mid(b, c);
  line ab(a, b), bc(b, c);
  line p_ab(-ab.b, ab.a, m_ab);
  line p_bc(-bc.b, bc.a, m_bc);
  double x_ab = p_ab.get();
  double x_bc = p_bc.get();
  return x_ab > x_bc || fabs(x_ab - x_bc) <= 1e-6;
}

inline long long sqr(int x) {
  return 1LL * x * x;
}

inline long long dist(const point& a, const point& b) {
  return sqr(a.x - b.x) + sqr(a.y - b.y);
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d %d", &n, &y);
  y <<= 1;
  for (int i = 1; i <= n; ++i) {    
    scanf("%d", &f[i].x);
    f[i].x <<= 1;
    f[i].y = y;
  }
  int m;
  scanf("%d", &m);
  for (int i = 1; i <= m; ++i) {
    scanf("%d %d", &t[i].x, &t[i].y);
    t[i].x <<= 1;
    t[i].y <<= 1;
    if (t[i].y < y) {
      t[i].y = (y << 1) - t[i].y;
    }
  }
  std::sort(f + 1, f + n + 1);
  std::sort(t + 1, t + m + 1);
  m = std::unique(t + 1, t + m + 1) - t - 1;  
  int sz = 0;
  for (int i = 1; i <= m; ++i) {
    while (sz > 1 && check(t[stack[sz - 1]], t[stack[sz]], t[i])) {
      --sz;
    }
    stack[++sz] = i;
  }
  long long ans = 0;
  for (int i = 1, j = 1; i <= n; ++i) {
    while (j < sz && dist(f[i], t[stack[j + 1]]) < dist(f[i], t[stack[j]])) {
      ++j;
    }
    long long val = dist(f[i], t[stack[j]]);
    if (val > ans) {
      ans = val;
    }
  }
  printf("%.6lf", sqrt(ans * 0.25));
}

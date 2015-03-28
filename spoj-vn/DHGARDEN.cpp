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
 
p2 p[12];
p2 arr[12];
std::vector<p2> v;
 
typedef long double ld;
 
const ld pi = 3.14159265358979323846264338327950288;
const ld eps = 1e-20;
 
#define sqr(a) ((a) * (a))
 
inline bool eq(const ld& a, const ld& b) {
  return fabs(a - b) <= eps * fabs(a);
}
 
inline ld dist(const p2& a, const p2& b) {
  return sqrt(sqr(1ll * a.first - b.first) + sqr(1ll * a.second - b.second));
}
 
int part(const p2& p) {
  if (p.first > 0 && p.second >= 0) return 1;
  if (p.first <= 0 && p.second > 0) return 2;
  if (p.first < 0 && p.second <= 0) return 3;
  return 4;
}
 
bool ok(const p2& a, const p2& b, const p2& c) {
  return a.first * b.second + b.first * c.second + c.first * a.second -
         a.second * b.first - b.second * c.first - c.second * a.first > 0;
}
 
bool cmp(p2 a, p2 b) {
  a.first -= v[0].first, a.second -= v[0].second;
  b.first -= v[0].first, b.second -= v[0].second;
  int xa = part(a);
  int xb = part(b);
  assert(xa <= 2);
  assert(xb <= 2);
  if (xa != xb) return xa < xb;
  int va = a.second * b.first;
  int vb = a.first * b.second;
  if (va != vb) return va < vb;
  return a.first + a.second < b.first + b.second;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int tt;
  for (scanf("%d", &tt); tt--; ) {
    int d, n, r;
    scanf("%d %d %d", &d, &n, &r);
    for (int i = 0; i < n; ++i)
      scanf("%d %d", &p[i].first, &p[i].second);
    int ans = 0;
    for (int mask = 1; mask < 1 << n; ++mask) {
      v.clear();
      for (int i = 0; i < n; ++i)
        if (mask & (1 << i))
          v.push_back(p[i]);
      for (size_t i = 1; i < v.size(); ++i)
        if (v[i].second < v[0].second ||
           (v[i].second == v[0].second && v[i].first < v[0].first))
          std::swap(v[0], v[i]);
      std::sort(v.begin() + 1, v.end(), cmp);
      int sz = 0;
      arr[sz++] = v[0];
      for (size_t i = 1; i < v.size(); ++i) {
        while (sz >= 2 && !ok(arr[sz - 2], arr[sz - 1], v[i]))
          --sz;
        arr[sz++] = v[i];
      }
      ld k = pi * 2 * r;
      for (int i = 1; i < sz; ++i)
        k += dist(arr[i], arr[i - 1]);
      k += dist(arr[sz - 1], arr[0]);
      if (k < d || eq(k, d)) ans = std::max(ans, int(v.size()));
    }
    printf("%d\n", ans);
  }
}
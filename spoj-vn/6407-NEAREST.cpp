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
 
const int N = 100010;
 
typedef std::pair<double, double> p2;
 
p2 p[N];
p2 arr[N];
double ans;
 
inline double sqr(double x) {
  return x * x;
}
 
inline double dist(const p2& x, const p2& y) {
  return sqr(x.first - y.first) + sqr(x.second - y.second);
}
 
bool cmp(const p2& x, const p2& y) {
  return x.second < y.second;
}
 
void solve(int f, int t) {
  if (f == t) return;
  int m = (f + t) >> 1;
  solve(f, m);
  solve(m + 1, t);
  int sz = 0;
  for (int i = f; i <= t; ++i)
    if (sqr(p[i].first - p[m].first) < ans)
      arr[++sz] = p[i];
  std::sort(arr + 1, arr + sz + 1, cmp);
  for (int i = 1; i <= sz; ++i)
    for (int j = i + 1; j <= sz && sqr(arr[j].second - arr[i].second) < ans; ++j) {
      double val = dist(arr[i], arr[j]);
      ans = std::min(ans, val);
    }
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%lf %lf", &p[i].first, &p[i].second);
  std::sort(p + 1, p + n + 1);  
  ans = 1e18;
  solve(1, n);
  printf("%.3lf", sqrt(ans));
}
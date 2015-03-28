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
 
const int inf = 1e9;
 
int a, b;
const int N = 1e6;
const int C = ~(1 << 31);
const int M = (1 << 16) - 1;
 
struct ele {
  int x, y, z;
} p[303030];
 
int dp[303030];
 
int r() {
  a = 36969 * (a & M) + (a >> 16);
  b = 18000 * (b & M) + (b >> 16);
  return (C & ((a << 16) + b)) % N;
}
 
bool cmp(const ele& a, const ele& b) {
  return a.z < b.z;
}
 
std::set<p2> st[303030];
 
inline void add(int x, int v) {
  if (st[v].size() == 0) {
    st[v].insert(p2(p[x].x, p[x].y));
    return;
  }
  std::set<p2>::iterator it = st[v].lower_bound(p2(p[x].x, p[x].y));
  if (it != st[v].begin()) {
    std::set<p2>::iterator j = it;
    --j;
    if (j->first <= p[x].x && j->second <= p[x].y) return;
  }
  while (it != st[v].end() && it->second >= p[x].y)
    st[v].erase(it++);
  st[v].insert(p2(p[x].x, p[x].y));
}
 
inline bool check(int x, int v) {
  if (st[v].size() == 0) return 0;
  std::set<p2>::iterator it = st[v].lower_bound(p2(p[x].x, -inf));
  if (it == st[v].begin()) return 0;
  --it;
  return it->second < p[x].y;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int m, n;
  while (scanf("%d %d %d %d", &m, &n, &a, &b)) {
    if (m == 0 && n == 0 && a == 0 && b == 0) break;
    for (int i = 1; i <= m; ++i)
      scanf("%d %d %d", &p[i].x, &p[i].y, &p[i].z);
    for (int i = 1; i <= n; ++i) {
      p[m + i].x = r();
      p[m + i].y = r();
      p[m + i].z = r();
    }
    n += m;
    std::sort(p + 1, p + n + 1, cmp);
    for (int i = 1; i <= n; ++i) st[i].clear();
    int ans = 0;
    for (int i = 1, j, t = 0; i <= n; i = j, ++t) {
      j = i;
      while (j <= n && p[j].z == p[i].z) ++j;
      for (int k = i; k < j; ++k) {
        int val = 0;
        for (int lo = 1, hi = t; lo <= hi; ) {
          int mi = (lo + hi) >> 1;
          if (check(k, mi)) {
            val = mi;
            lo = mi + 1;
          } else {
            hi = mi - 1;
          }
        }
        ++val;
        ans = std::max(ans, val);
        dp[k] = val;
      }
      for (int k = i; k < j; ++k) add(k, dp[k]);
    }
    printf("%d\n", ans);
  }
}
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
 
int k[202020];
int x[202020];
int f[202020];
int t[202020];
 
int vn;
int v[202020];
 
int fw[202020];
 
void update(int i, int v) {
  for ( ; i <= vn; i += i & -i)
    fw[i] += v;
}
 
int query(int i) {
  int res = 0;
  for ( ; i; i -= i & -i)
    res += fw[i];
  return res;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    char s[2];
    scanf("%s %d", s, x + i);
    if (*s == '?') {
      scanf("%d %d", f + i, t + i);
    } else {
      v[++vn] = x[i];
      if (*s == '+') k[i] = 1;
      else           k[i] = -1;
    }
  }
  std::sort(v + 1, v + vn + 1);
  vn = std::unique(v + 1, v + vn + 1) - v - 1;
  for (int i = 1; i <= n; ++i) {
    if (k[i] == 0) {
      int pf = std::lower_bound(v + 1, v + vn + 1, f[i]) - v;
      int pt = std::upper_bound(v + 1, v + vn + 1, t[i]) - v - 1;
      int cf = query(pf - 1);
      int ct = query(pt);
      if (ct - cf < x[i]) {
        puts("0");
      } else {
        int ans = -1;
        for (int lo = pf, hi = pt; lo <= hi; ) {
          int mi = (lo + hi) >> 1;
          int cm = query(mi);
          if (cm - cf >= x[i]) {
            hi = mi - 1, ans = mi;
          } else {
            lo = mi + 1;
          }
        }
        assert(ans != -1);
        printf("%d\n", v[ans]);
      }
    } else {
      int p = std::lower_bound(v + 1, v + vn + 1, x[i]) - v;
      update(p, k[i]);
    }
  }
}
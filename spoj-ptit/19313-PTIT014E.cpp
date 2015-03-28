#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
const int inf = 2e9;
 
int x[101], y[101];
bool b[101];
 
inline void ff(int x, int y, int& fx, int& tx, int& fy, int& ty) {
  if (x < fx) fx = x;
  if (x > tx) tx = x;
  if (y < fy) fy = y;
  if (y > ty) ty = y;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);  
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d %d", x + i, y + i);
    int ans1 = -1;
    int ans2 = -1;
    {
      int fx = inf, tx = -inf;
      int fy = inf, ty = -inf;
      for (int i = 1; i <= n; ++i)
        ff(x[i], y[i], fx, tx, fy, ty);
      // bl - tr
      {
        int v = -1;
        int lo = 1;
        int hi = inf;
        while (lo <= hi) {
          int mi = (0ll + lo + hi) >> 1;
          bool f = true;
          for (int i = 1; i <= n && f; ++i)
            f = (x[i] <= fx + mi && y[i] <= fy + mi) || (tx - mi <= x[i] && ty - mi <= y[i]);
          if (f) {
            v = mi;
            hi = mi - 1;
          } else {
            lo = mi + 1;          
          }
        }
        if (ans1 == -1 || ans1 > v)
          ans1 = v;
      }
      // br - tl
      {
        int v = -1;
        int lo = 1;
        int hi = inf;
        while (lo <= hi) {
          int mi = (0ll + lo + hi) >> 1;
          bool f = true;
          for (int i = 1; i <= n && f; ++i)
            f = (x[i] <= fx + mi && ty - mi <= y[i]) || (tx - mi <= x[i] && y[i] <= fy + mi);
          if (f) {
            v = mi;
            hi = mi - 1;
          } else {
            lo = mi + 1;          
          }
        }
        if (ans1 == -1 || ans1 > v)
          ans1 = v;
      }
    }
    {
      for (int i = 1; i <= n; ++i) {
        // vertical
        {
          int lfy = inf, lty = -inf;
          int lfx = inf, ltx = -inf, lc = 0;
          int rfy = inf, rty = -inf;
          int rfx = inf, rtx = -inf, rc = 0;
          for (int j = 1; j <= n; ++j) {
            if (x[j] < x[i]) {
              ++lc;
              ff(x[j], y[j], lfx, ltx, lfy, lty);
            } else {
              ++rc;
              ff(x[j], y[j], rfx, rtx, rfy, rty);
            }
          }
          int lsz = lc ? std::max(ltx - lfx, lty - lfy) : 1;
          int rsz = rc ? std::max(rtx - rfx, rty - rfy) : 1;
          int v = std::max(lsz, rsz);
          if (ans2 == -1 || ans2 > v) ans2 = v;
        }
        // horizontal
        {
          int tfy = inf, tty = -inf;
          int tfx = inf, ttx = -inf, tc = 0;
          int bfy = inf, bty = -inf;
          int bfx = inf, btx = -inf, bc = 0;
          for (int j = 1; j <= n; ++j) {
            if (y[j] < y[i]) {
              ++bc;
              ff(x[j], y[j], bfx, btx, bfy, bty);
            } else {
              ++tc;
              ff(x[j], y[j], tfx, ttx, tfy, tty);
            }
          }
          int bsz = bc ? std::max(btx - bfx, bty - bfy) : 1;
          int tsz = tc ? std::max(ttx - tfx, tty - tfy) : 1;
          int v = std::max(bsz, tsz);
          if (ans2 == -1 || ans2 > v) ans2 = v;
        }
      }
    }
    assert(ans1 != -1);
    assert(ans2 != -1);
    if (ans2 == 0) ans2 = 1;
    printf("%d %d\n", ans1, ans2);
  }
} 
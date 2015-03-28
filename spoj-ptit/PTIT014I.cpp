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
 
typedef std::pair<int, int> p2;
 
int a[1010];
int b[1010];
int c[1010][1010];
 
struct p3 {
  int i, j, v;
  p3() { }
  p3(int i, int j, int v) : i(i), j(j), v(v) { }
  bool operator< (const p3& a) const {
    return v < a.v;
  }
} ax[1010101], ay[1010101];
 
p2 rx[1010101];
p2 ry[1010101];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  while (~scanf("%d", &n))
    if (n) {
      for (int i = 1; i <= n; ++i)
        scanf("%d", a + i);
      std::sort(a + 1, a + n + 1);
      int nx = 0;
      int ny = 0;
      for (int i = 1; i < n; ++i)
        for (int j = i + 1; j <= n; ++j)
          ax[++nx] = p3(i, j, a[i] + a[j]);
      for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
          if (i != j)
            ay[++ny] = p3(i, j, a[i] - a[j]);
      std::sort(ax + 1, ax + nx + 1);
      std::sort(ay + 1, ay + ny + 1);
      int ix = 1;
      int iy = 1;
      long long cnt = 0;
      int best = -inf;
      while (ix <= nx && iy <= ny) {
        if (ax[ix].v < ay[iy].v) {
          ++ix;
        } else if (ay[iy].v < ax[ix].v) {
          ++iy;
        } else {
          int val = ax[ix].v;
          int jx = ix, jy = iy;
          int cx = 0, cy = 0;
          rx[++cx] = p2(ax[ix].i, ax[ix].j);
          ry[++cy] = p2(ay[iy].i, ay[iy].j);
          while (jx + 1 <= nx && ax[jx + 1].v == ax[ix].v) ++jx, rx[++cx] = p2(ax[jx].i, ax[jx].j);
          while (jy + 1 <= ny && ay[jy + 1].v == ay[iy].v) ++jy, ry[++cy] = p2(ay[jy].i, ay[jy].j);
          for (int i = 1; i <= cy; ++i) {
            if (val + a[ry[i].first] == a[ry[i].second]) {
              if (best < a[ry[i].second])
                best = a[ry[i].second];
            } else {
              if (best < a[ry[i].first])
                best = a[ry[i].first];
            }
            ++b[ry[i].first];
            ++b[ry[i].second];
            ++c[ry[i].first][ry[i].second];
          }
          for (int i = 1; i <= cx; ++i)
            cnt += (cy - b[rx[i].first]) + (cy - b[rx[i].second]) - (cy - c[rx[i].first][rx[i].second] - c[rx[i].second][rx[i].first]);
          for (int i = 1; i <= cy; ++i) {
            b[ry[i].first] = 0;
            b[ry[i].second] = 0;
            c[ry[i].first][ry[i].second] = 0;
          }
          ix = jx + 1;
          iy = jy + 1;
        }
      }
      if (cnt) {
        printf("%lld %d\n", cnt / 3, best);
      } else {
        puts("0");
      }
    }
} 
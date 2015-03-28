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
 
struct item {
  int x, y, s;
  bool operator< (const item& a) const {
    return x < a.x;
  }
} a[1515];
 
std::vector<p2> va[101];
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d %d %d", &a[i].x, &a[i].y, &a[i].s);
    a[i].s = a[i].s * a[i].s + 5;
  }
  std::sort(a + 1, a + n + 1);
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= 100; ++j)
      va[j].clear();
    for (int j = i + 1; j <= n; ++j) {
      int dx = a[j].x - a[i].x;
      int dy = a[j].y - a[i].y;
      int g = std::__gcd(dx, dy);
      dx /= g;
      dy /= g;
      if (dx < 0) dx = -dx, dy = -dy;
      va[dx].push_back(p2(dy, a[j].s));
    }
    int val = 0;
    for (int j = 0; j <= 100; ++j) {
      std::sort(va[j].begin(), va[j].end());
      std::vector<p2>& vx = va[j];
      for (size_t k = 0; k < vx.size(); ) {
        size_t p = k + 1;
        int tot = vx[k].second;
        while (p < vx.size() && vx[p].first == vx[k].first)
          tot += vx[p++].second;
        val = std::max(val, tot);
        k = p;
      }
    }
    ans = std::max(ans, val + a[i].s);
  }
  printf("%d", ans);
}
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
typedef std::pair<int, int> p2;
 
std::map<p2, int> st[2020];
int x[2020], y[2020], z[2020];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d %d %d", x + i, y + i, z + i);
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= 2000; ++j)
      st[j].clear();
    int t = 0;
    for (int j = i + 1; j <= n; ++j) {
      int dx = x[j] - x[i];
      int dy = y[j] - y[i];
      int dz = z[j] - z[i];
      int g = std::__gcd(dx, std::__gcd(dy, dz));
      if (g) {
        dx /= g;
        dy /= g;
        dz /= g;
      }
      if (dz < 0) {
        dx = -dx;
        dy = -dy;
        dz = -dz;
      }
      if (dz > 0) {
        ++st[dz][p2(dx, dy)];
      } else if (dx == 0 && dy == 0) {
        ++t;
      }
    }
    ans = std::max(ans, t);
    for (int j = 1; j <= 2000; ++j)
      for (std::map<p2, int>::iterator it = st[j].begin(); it != st[j].end(); ++it)
        ans = std::max(ans, it->second + t);
  }
  printf("%d\n", ans + 1);
} 
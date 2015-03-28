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
 
p2 a[101010];
int dp[101010];
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i].first);
    a[i].second = i;
  }
  std::sort(a + 1, a + n + 1);
  int ans = 1;
  for (int d = 1; d <= 100; ++d) {
    std::fill(dp + 1, dp + n + 1, 1);
    for (int i = 1, j = 1; i <= n; ) {
      while (j <= n && a[j].first - a[i].first < d) ++j;
      int ki = i + 1;
      while (ki <= n && a[ki].first == a[i].first) ++ki;
      int kj = j + 1;
      while (kj <= n && a[kj].first == a[j].first) ++kj;
      if (a[j].first - a[i].first == d) {
        int mx = 0;
        for ( ; j < kj; ++j) {
          while (i < ki && a[i].second < a[j].second)
            mx = std::max(mx, dp[i++]);
          dp[j] = mx + 1;
        }
      }
      i = ki;
    }
    for (int i = 1; i <= n; ++i)
      ans = std::max(ans, dp[i]);
  }
  printf("%d", ans);
}
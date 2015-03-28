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
 
struct ele {
  int l, p, s;
} a[111];
 
bool cmp(const ele& x, const ele& y) {
  return x.s < y.s;
}
 
int dp[16161];
int tmp[16161];
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, k;
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= k; ++i)
    scanf("%d %d %d", &a[i].l, &a[i].p, &a[i].s);
  std::sort(a + 1, a + k + 1, cmp);
  for (int i = 1; i <= k; ++i) {
    int l = a[i].l;
    int p = a[i].p;
    int s = a[i].s;
    int lb = std::max(1, s - l + 1);
    int rb = std::min(n, s + l - 1);
    std::copy(dp + lb - 1, dp + s, tmp + lb - 1);
    for (int j = s - 1, v = 0; j >= lb - 1; --j, v += p)
      tmp[j] += v;
    for (int j = s - 2; j >= lb - 1; --j)
      tmp[j] = std::max(tmp[j], tmp[j + 1]);
    for (int j = s, v = p; j <= rb; ++j, v += p) {
      int x = std::max(0, j - l);
      dp[j] = std::max(dp[j], tmp[x] + v);
    }
  }
  int ans = *std::max_element(dp + 1, dp + n + 1);
  printf("%d", ans);
}
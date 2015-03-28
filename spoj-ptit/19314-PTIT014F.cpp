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
 
const long long inf = 1ll << 60;
 
typedef std::pair<long long, int> p2;
 
long long a[202020];
long long b[202020];
long long dp[202020];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n, r;
    scanf("%d %d", &n, &r);
    for (int i = 1; i <= n; ++i) {
      scanf("%lld", a + i);
      b[i] = b[i - 1] + a[i];
    }
    for (int i = 0; i <= n; ++i)
      dp[i] = -inf;
    long long x = -inf;
    std::deque<p2> de;
    for (int i = 1; i <= n; ++i) {
      int lb = std::max(1, i - r);
      int rb = std::min(n, i + r);
      dp[rb] = std::max(dp[rb], b[rb] - b[lb - 1]);
      dp[rb] = std::max(dp[rb], x + b[rb] - b[lb - 1]);
      if (!de.empty()) dp[rb] = std::max(dp[rb], de.front().first + b[rb]);
      int nlb = std::max(1, i + 1 - r);
      int nrb = std::min(n, i + 1 + r);
      if (nlb > 1) x = std::max(x, dp[nlb - 1]);
      if (rb < nrb) {
        long long val = dp[rb] - b[rb];
        while (!de.empty() && de.back().first <= val) de.pop_back();      
        while (!de.empty() && de.front().second < nlb) de.pop_front();
        de.push_back(p2(val, i));
      }
    }
    long long ans = -inf;
    for (int i = 1; i <= n; ++i)
      ans = std::max(ans, dp[i]);
    assert(ans != -inf);
    printf("%lld\n", ans);
  }
} 
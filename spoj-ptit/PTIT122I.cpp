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
 
typedef std::pair<long long, long long> p2;
 
long long inf = 1e15 + 5;
 
std::vector<p2> ans;
std::vector<p2> vec;
long long dp[155][155];
 
long long nCk(long long n, int k) {
  if (k <= 10) {
    long double val = 1;
    for (long long x = n - k + 1; x <= n; ++x)
      val *= x;
    for (int x = 2; x <= k; ++x)
      val /= x;
    if (val > inf) return inf;
    return (long long)val;
  } else {
    if (n > 150) return inf;
    return dp[n][k];
  }
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  for (int i = 1; i <= 150; ++i)
    dp[i][0] = dp[i][i] = 1;
  for (int i = 2; i <= 150; ++i)
    for (int j = 1; j < i; ++j) {
      long double val = dp[i - 1][j] + dp[i - 1][j - 1];
      dp[i][j] = val > inf ? inf : val;
    }
  int tt;
  for (scanf("%d", &tt); tt--; ) {
    long long m;
    scanf("%lld", &m);
    int k = 1;
    long long n = m;
    ans.clear();
    while (n >= k << 1) {
      if (nCk(n, k) == m) ans.push_back(p2(n, k));
      ++k;
      long long x = -1;
      for (long long lo = 1, hi = n; lo <= hi; ) {
        long long mi = (lo + hi) >> 1;
        long long val = nCk(mi, k);
        if (val <= m) lo = mi + 1, x = mi;
        else hi = mi - 1;
      }
      n = x;
    }
    vec.clear();
    for (std::vector<p2>::reverse_iterator i = ans.rbegin(); i != ans.rend(); ++i) {
      vec.push_back(*i);
      assert(i->first >= i->second << 1);
      if (i->first - i->second != i->second)
        vec.push_back(p2(i->first, i->first - i->second));
    }    
    printf("%d\n", vec.size());
    for (size_t i = 0; i < vec.size() - 1; ++i)
      printf("(%lld,%lld) ", vec[i].first, vec[i].second);
    printf("(%lld,%lld)\n", vec.back().first, vec.back().second);
  }
}
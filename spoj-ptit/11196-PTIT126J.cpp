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
 
const int inf = 1e9;
 
int a[1010101];
long long pfx[1010101];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%d", a + i);  
  std::sort(a + 1, a + n + 1);
  for (int i = n; i >= 1; --i)
    pfx[i] = pfx[i + 1] + a[i];
  int lo = 1;
  int hi = inf;
  int ans = -1;
  while (lo <= hi) {
    int mi = (lo + hi) >> 1;  
    int p = std::lower_bound(a + 1, a + n + 1, mi) - a;
    long long v = pfx[p] - 1ll * (n - p + 1) * mi;
    if (v == m) {
      ans = mi;
      break;
    }
    if (v > m) {
      lo = mi + 1;
      ans = mi;
    } else {
      hi = mi - 1;
    }
  }
  printf("%d", ans);
} 
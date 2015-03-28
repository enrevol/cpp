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
 
int a[101010];
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, s;
  scanf("%d %d", &n, &s);
  for (int i = 1; i <= n; ++i)
    scanf("%d", a + i);
  std::sort(a + 1, a + n + 1);
  long long ans = 0;
  int l = 1;
  int r = n;
  while (l <= r) {
    long long v = a[l] + a[r];
    if (v > s) {
      --r;
    } else if (v < s) {
      ++l;
    } else {
      int xl = l + 1;
      while (a[xl] == a[l]) ++xl;
      int xr = r - 1;
      while (a[xr] == a[r]) --xr;
      int cl = xl - l;
      int cr = r - xr;
      if (a[l] == a[r]) {
        assert(cl == cr);
        ans += 1ll * cl * (cl - 1) / 2;
      } else {
        ans += 1ll * cl * cr;
      }
      l = xl;
      r = xr;
    }
  }
  printf("%lld", ans);
}
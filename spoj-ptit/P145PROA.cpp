#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
long long p10[22], ans;
int sz, arr[22];
 
inline int ff(int v, int k) {
  int f = std::max(v - 9, k);
  int t = std::min(v, 9);
  return t - f + 1;
}
 
void dfs(int f, int t, long long n) {
  if (n < 0) return;
  if (f > t) {
    if (n == 0) {
      /*for (int i = 0; i < f; ++i)
          printf("%d ", arr[i]);
        putchar('\n');*/
      long long tot = 1;
      if ((f - t) & 1) {
        tot = ff(arr[0], 1);
        for (int i = 1; i < f; ++i)
        tot *= ff(arr[i], 0);
      } else {
        if (f > 1) tot = ff(arr[0], 1);
        for (int i = 1; i < f - 1; ++i)
          tot *= ff(arr[i], 0);
      }
      ans += tot;
    }
  } else {
    long long s = p10[f] + p10[t];
    if (f < t) {
      if (n > s * 20) return;
      for (int i = 0; i <= 18; ++i) {
        arr[f] = i;
        dfs(f + 1, t - 1, n - s * i);
      }
    } else {
      if (n > s * 10) return;
      for (int i = 0; i <= 9; ++i) {
        arr[f] = i;
        dfs(f + 1, t - 1, n - s * i);
      }
    }
  }
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  p10[0] = 1;
  for (int i = 1; i <= 18; ++i)
    p10[i] = p10[i - 1] * 10;
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    long long n;
    scanf("%lld", &n);
    sz = 0;
	  long long nn = n;
    while (n) {
      n /= 10;
      ++sz;
    }
    ans = 0;
    dfs(0, sz - 1, nn);
    if (sz > 1) dfs(0, sz - 2, nn);
    printf("%lld\n", ans);
  }
} 
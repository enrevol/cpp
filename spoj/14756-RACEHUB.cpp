#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
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
 
const int N = 100010;
 
int a[N];
long long sum[N];
 
long long calc_left(int f, int t) {
  long long res = 0;
  // for (int k = f; k < t; ++k)
  //   res = res + (a[t] - a[k]);
  // res = a[t] * (t - f) - (a[f] + ... + a[t-1]);
  res = 1LL * a[t] * (t - f) - (sum[t - 1] - sum[f - 1]);  
  return res;
}
 
long long calc_right(int f, int t) {
  long long res = 0;
  // for (int k = f + 1; k <= t; ++k)
  //   res = res + (a[k] - a[f]);
  // res = (a[t] + ... + a[f+1]) - a[f] * (t - f);
  res = (sum[t] - sum[f]) - 1LL * a[f] * (t - f);
  return res;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, l;
  long long b;
  scanf("%d %d %lld", &n, &l, &b);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a + i);
    sum[i] = sum[i - 1] + a[i];
  }
  int ans = 0;
  for (int f = 1, t = n; f <= t; ) {
    int m = (f + t) >> 1;
    bool ok = 0;
    //fprintf(stderr, "m = %d\n", m);
    for (int i = 1; i + m - 1 <= n && !ok; ++i) {
      int pos = (i + m - 1 + i) >> 1;
      long long tot = calc_left(i, pos) + calc_right(pos, i + m - 1);
      //fprintf(stderr, "f = %d t = %d p = %d tot = %lld\n", i, i + m - 1, pos, tot);
      ok = tot <= b;
    }
    if (ok) {
      ans = m;
      f = m + 1;
    } else {
      t = m - 1;
    }
  }
  printf("%d", ans);
}
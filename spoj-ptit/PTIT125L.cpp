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
 
int a[50505];
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int l, n, m;
  scanf("%d %d %d", &l, &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%d", a + i);
  a[++n] = 0;
  a[++n] = l;
  std::sort(a + 1, a + n + 1);
  int ans = -1;
  for (int lo = 1, hi = l; lo <= hi; ) {
    int mi = (lo + hi) >> 1;
    int cnt = 0;
    for (int i = 1; i <= n; ) {
      int j = i + 1;
      while (j <= n && a[j] - a[i] < mi)
        ++cnt, ++j;
      i = j;
    }
    if (cnt <= m) lo = mi + 1, ans = mi;
    else hi = mi - 1;
  }
  assert(ans != -1);
  printf("%d", ans);
}
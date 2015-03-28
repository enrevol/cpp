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
 
int a[10][10];
int p[10];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        scanf("%d", a[i] + j);
    for (int i = 1; i <= n; ++i)
      p[i] = i;
    long long best = 1ll << 60;
    do {
      long long v = 0;
      for (int i = 1; i <= n; ++i)
        v += a[i][p[i]];
      if (v < best) best = v;
    } while (std::next_permutation(p + 1, p + n + 1));
    printf("%lld\n", best);
  }
} 
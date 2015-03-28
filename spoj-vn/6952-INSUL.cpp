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
 
int a[101010];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  long long ans = 0;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a + i);
    ans += a[i];
  }
  std::sort(a + 1, a + n + 1);
  int l = 1;
  int r = n;
  while (l <= r)
    ans += a[r--] - a[l++];
  printf("%lld", ans);
} 
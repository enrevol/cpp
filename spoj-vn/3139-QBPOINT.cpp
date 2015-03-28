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
 
typedef std::pair<int, int> p2;
 
p2 a[2020];
p2 arr[2020];
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d %d", &a[i].first, &a[i].second);
  long long ans = 0;
  for (int i = 1; i <= n; ++i) {
    int sz = 0;
    for (int j = i + 1; j <= n; ++j) {
      int dx = a[j].first - a[i].first;
      int dy = a[j].second - a[i].second;
      int k = std::__gcd(dx, dy);
      arr[++sz] = p2(dx / k, dy / k);
    }
    std::sort(arr + 1, arr + sz + 1);
    for (int j = 1; j <= sz; ) {
      int k = j + 1;
      while (k <= sz && arr[k] == arr[j]) ++k;
      int d = k - j;
      ans += d * (d - 1);
      j = k;
    }
  }
  printf("%lld", ans >> 1);
}
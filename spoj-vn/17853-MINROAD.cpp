#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
#define m2 std::make_pair
 
typedef std::pair<int, int> p2;
 
p2 d[303030];
int c_a[303030], c_b[303030];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);  
  int n, a, b;
  scanf("%d %d %d", &n, &a, &b);
  for (int i = 1; i <= n; ++i)
    scanf("%d %d", &d[i].first, &d[i].second);
  std::sort(d + 1, d + n + 1);
  for (int i = 1; i <= n; ++i) {
    c_a[i] = c_a[i - 1] + (d[i].second == 1);
    c_b[i] = c_b[i - 1] + (d[i].second == 2);
  }
  int ans = -1;
  int l = 1, r = d[n].first;
  while (l <= r) {    
    int m = (l + r) >> 1;
    int f = 0;
    int s = 1, e = 1;
    for (int i = 1; i <= n && !f; ++i) {
      int pos = std::upper_bound(d + 1, d + n + 1, m2(d[i].first + m, 2)) - d - 1;
      if (c_a[pos] - c_a[i - 1] >= a && c_b[pos] - c_b[i - 1] >= b)
        f = 1;
    }
    if (f) {
      ans = m;
      r = m - 1;
    } else {
      l = m + 1;
    }
  }
  printf("%d", ans);
} 
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
 
int a[20202], b[20202], c[101010], t[101010];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n, x, y, z;
  scanf("%d %d %d %d", &n, &x, &y, &z);
  int d = 0;
  for (int i = 1; i <= n; ++i) {
    scanf("%d %d", a + i, b + i);
    c[++d] = a[i] - 1;
    c[++d] = a[i];
    c[++d] = b[i];
    c[++d] = b[i] + 1;
  }
  std::sort(c + 1, c + d + 1);
  d = std::unique(c + 1, c + d + 1) - c - 1;
  for (int i = 1; i <= n; ++i) {
    int pos_a = std::lower_bound(c + 1, c + d + 1, a[i]) - c - 1;
    int pos_b = std::lower_bound(c + 1, c + d + 1, b[i]) - c - 1;
    t[1] += x;
    t[pos_a] += y - x;
    t[pos_b + 1] += z - y;
  }
  int ans = 0;
  for (int i = 2; i <= d; ++i) {
    t[i] += t[i - 1];
    if (t[i] > ans) ans = t[i];
  }
  printf("%d", ans);
} 
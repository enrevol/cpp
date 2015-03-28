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

int a[7][7];

int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n, a;
  scanf("%d %d", &n, &a);
  int m = 1, d = 0;
  while (m <= a) {
    m *= 10;
    ++d;
  }
  int ans = 0;
  while (n) {
    int t = std::min(m - a, n);
    n -= t;
    ans += t * d;
    a = m;
    m *= 10;
    ++d;
  }
  printf("%d", ans);
}
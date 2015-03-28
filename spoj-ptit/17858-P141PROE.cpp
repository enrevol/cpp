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
 
char s[111];
 
int n;
 
int ff(const int& i, const int& j, const int& k, const int& x, const int& y, const int& z) {
  int dx = std::abs(i - x);
  dx = std::min(dx, n - dx);
  int dy = std::abs(j - y);
  dy = std::min(dy, n - dy);
  int dz = std::abs(k - z);
  dz = std::min(dz, n - dz);
  return std::max(dx, std::max(dy, dz));
}
 
int main() {  
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  scanf("%d", &n);
  int a, b, c;
  scanf("%d %d %d", &a, &b, &c);
  int x, y, z;
  scanf("%d %d %d", &x, &y, &z);
  int ans = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      for (int k = 1; k <= n; ++k)
        ans += ff(i, j, k, a, b, c) <= 2 || ff(i, j, k, x, y, z) <= 2;
  printf("%d", ans);
}
 
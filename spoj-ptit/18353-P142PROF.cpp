#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
const int w = 1e3;
 
int a[w + 10];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n;
  while (~scanf("%d", &n)) {
    for (int i = 1; i <= n; ++i)
      scanf("%d", a + i);
    std::sort(a + 1, a + n + 1, std::greater<int>());
    for (int i = 1; i <= n; ++i) {
      bool f = true;
      for (int j = 1; j <= n && f; ++j)
        if (i != j)
          if (std::__gcd(a[i], a[j]) > 1)
            f = false;
      if (f) {
        printf("%d\n", a[i]);
        break;
      }
    }
  }
} 
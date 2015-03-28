#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
const int mod = 1 << 30;
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int a, b, c;
  scanf("%d %d %d", &a, &b, &c);
  int ans = 0;
  for (int i = 1; i <= a; ++i)
    for (int j = 1; j <= b; ++j)
      for (int k = 1; k <= c; ++k) {
        int t = i * j * k;
        int d = 1;
        int it = 2;
        while (it * it <= t) {
          int p = 0;
          while (t % it == 0) {
            ++p;
            t /= it;
          }
          d *= p + 1;
          ++it;
        }
        if (t > 1) d <<= 1;
        ans += d;
      }
  printf("%d", ans);
} 
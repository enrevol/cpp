#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  long long ans = 0;
  if (n <= 2) {
    ans = n;
  } else {    
    if (n & 1) {
      ans = 1ll * n * (n - 1) * (n - 2);
    } else {
      ans = 1ll * (n - 1) * (n - 2) * (n - 3);
      long long k = 1ll * n * (n - 1);
      for (int i = n; i >= 1; --i)
        if (std::__gcd(i, n) == 1 && std::__gcd(i, n - 1) == 1) {
          ans = std::max(ans, k * i);
          break;
        }
    }
  }
  printf("%lld", ans);
} 
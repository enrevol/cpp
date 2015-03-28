#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <sstream>
#include <string>
#include <vector>
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    long long n;
    scanf("%lld", &n);
    long long ans = 0;
    for (long long i = 1; i * i <= n; ++i)
      if (n % i == 0) {
        ans += i;
        if (i * i < n) ans += n / i;
      }
    printf("%lld\n", ans);
  }
} 
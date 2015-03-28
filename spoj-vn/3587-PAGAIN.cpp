#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
typedef unsigned long long ull;
 
const ull num[] = { 2, 7, 61 };
 
ull pmod(ull a, ull n, const ull& m) {
  ull res = 1;
  while (n) {    
    if (n & 1) {
      res *= a;
      res %= m;
    }
    a *= a;
    a %= m;
    n >>= 1;
  }
  return res;
}
 
bool test(const ull& a, const ull& d, int s, const ull& n) {
  ull res = pmod(a, d, n);
  if (res == 1 || res == n - 1) {    
    return 1;
  } else {
    for (int r = 1; r < s; ++r) {
      res *= res;
      res %= n;
      if (res == n - 1) return 1;
    }
  }
  return 0;
}
 
bool solve(ull& n) {
  ull d = n - 1;
  int s = 0;
  while (!(d & 1)) {
    d >>= 1;
    ++s;
  }
  bool ans = 1;
  for (int i = 0; i < 3 && ans && num[i] < n; ++i)
    ans = test(num[i], d, s, n);
  return ans;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    ull n;
    scanf("%llu", &n);
    while (1) {
      --n;
      if (solve(n)) {
        printf("%llu\n", n);
        break;
      }
    }
  }
} 
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
 
void sh(unsigned long long& a, int s, const unsigned long long& m) {
  while (s--) {
    a <<= 1;
    a %= m;
  }
}
 
unsigned long long mul(const unsigned long long& a, const unsigned long long& b, const unsigned long long& m) {
  unsigned long long a_h = (a >> 32),
                     a_l = (a << 32) >> 32,
                     b_h = (b >> 32),
                     b_l = (b << 32) >> 32,
                     val_hh = (a_h * b_h) % m,
                     val_hl = (a_h * b_l) % m,
                     val_lh = (a_l * b_h) % m,
                     val_ll = (a_l * b_l) % m;
  sh(val_hh, 64, m);
  sh(val_lh, 32, m);
  sh(val_hl, 32, m);
  unsigned long long res = (val_hh + val_hl) % m;
  res = (res + val_lh) % m;
  res = (res + val_ll) % m;
  return res;
}
 
unsigned long long pmod(unsigned long long a, unsigned long long n, const unsigned long long& m) {
  unsigned long long res = 1;
  while (n) {    
    if (n & 1) res = mul(res, a, m) % m;
    a = mul(a, a, m) % m;
    n >>= 1;
  }
  return res;
}
bool test(const unsigned long long& a, const unsigned long long& d, const int& s, const unsigned long long& n) {
  unsigned long long res = pmod(a, d, n);
  if (res == 1 || res == n - 1) {    
    return 1;
  } else {
    for (int r = 1; r < s; ++r) {
      res = mul(res, res, n) % n;
      if (res == n - 1) return 1;
    }
  }
  return 0;
}
unsigned long long num[] = { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 };
bool solve(unsigned long long& n) {
  unsigned long long d = n - 1;
  int s = 0;
  while (!(d & 1)) {
    d >>= 1;
    ++s;
  }
  bool ans = 1;
  for (int i = 0; i < 7 && ans && num[i] < n; ++i)
    ans = test(num[i], d, s, n);
  return ans;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    unsigned long long n;
    scanf("%llu", &n);
    if (solve(n)){
      puts("YES");
    } else {
      puts("NO");
    }
  }
}
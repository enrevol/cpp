#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
const int mod = 20122007;
 
int pmod(int a, int b, int mod) {
  int res = 1;
  while (b) {
    if (b & 1) res = (1ll * res * a) % mod;
    a = (1ll * a * a) % mod;
    b >>= 1;
  }
  return res;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  int ans = 1;
  for (int i = 1; i * i <= n; ++i) {
    if (n % i == 0) {
      int val = pmod(3, i, mod) - 1;
      if (val < 0) val += mod;
      ans = (1ll * ans * val) % mod;
      if (i * i < n) {
        int val = pmod(3, n / i, mod) - 1;
        if (val < 0) val += mod;
        ans = (1ll * ans * val) % mod;
      }
    }
  }
  printf("%d", ans);
} 
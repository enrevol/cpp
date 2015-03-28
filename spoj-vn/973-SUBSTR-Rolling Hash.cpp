#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
const int mod = 1e9 + 7;
const int base = 47;
 
char a[1010101];
char b[1010101];
 
inline int pmod(int a, int b, int mod) {
  int res = 1;
  while (b) {
    if (b & 1) res = 1ll * res * a % mod;
    a = 1ll * a * a % mod;
    b >>= 1;
  }
  return res;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  scanf("%s", a + 1);
  scanf("%s", b + 1);
  int an = strlen(a + 1);
  int bn = strlen(b + 1);
  if (an < bn) return 0;
  int ah = 0;
  int bh = 0;
  const int k = pmod(base, bn - 1, mod);
  for (int i = 1; i <= bn; ++i) {
    bh = (1ll * bh * base + b[i]) % mod;
    ah = (1ll * ah * base + a[i]) % mod;
  }
  if (ah == bh) printf("1 ");
  for (int i = bn + 1; i <= an; ++i) {
    ah = ((ah - 1ll * a[i - bn] * k) * base + a[i]) % mod;
    if (ah < 0) ah += mod;
    if (ah == bh) printf("%d ", i - bn + 1);
  }
}
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
 
bool sieve[32000];
 
int pn;
int pr[5000];
 
long long bpow(long long a, int b) {
  long long res = 1;
  while (b) {
    if (b & 1) res *= a;
    a *= a;
    b >>= 1;
  }
  return res;
}
 
bool ok(int k) {
  for (int i = 1; i <= pn && pr[i] * pr[i] <= k; ++i)
    if (k % pr[i] == 0) return 0;
  return 1;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  for (int i = 2; i * i < 32000; ++i)
    if (!sieve[i])
      for (int j = i * i; j < 32000; j += i)
        sieve[j] = 1;
  for (int i = 2; i < 32000; ++i)
    if (!sieve[i])
      pr[++pn] = i;
  long long n;
  scanf("%lld", &n);
  for (int p = 2; p <= 60; ++p) {
    int k = pow(n, 1.0 / p);
    if (bpow(k, p) == n && ok(k)) { printf("%d %d", k, p); return 0; }
    if (bpow(k + 1, p) == n && ok(k + 1)) { printf("%d %d", k + 1, p); return 0; }
  }
  puts("0");
}
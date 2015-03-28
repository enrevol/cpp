#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
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
 
const int w = 1 << 27;
 
std::bitset<(w >> 1) + 10> sieve;
int p[(1 << 23) - 1];
 
typedef std::pair<long long, int> p2;
 
p2 fact[20];
int fn;
long long t;
 
int solve(int it, long long v) {
  if (v > t) return 0;
  if (it > fn) return 1;  
  int res = 0;
  for (int i = 0; i <= fact[it].second; ++i) {
    res += solve(it + 1, v);
    v *= fact[it].first;
  }
  return res;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  for (int i = 3; i * i <= w; i += 2)
    if (!sieve[i >> 1])
      for (int j = i * i; j <= w; j += i << 1)
        sieve[j >> 1] = true;  
  int pn = 0;
  p[++pn] = 2;
  for (int i = 3; i <= w; i += 2)
    if (!sieve[i >> 1])
      p[++pn] = i;
  int nc = 0;
  long long n, b;
  while (~scanf("%lld %lld %lld", &n, &t, &b)) {
    if (n | t | b) {
      t %= n;
      fn = 0;
      for (int i = 1; i <= pn && 1ll * p[i] * p[i] <= b && b > 1; ++i) {
        int x = 0;
        while (b % p[i] == 0) {
          b /= p[i];
          ++x;
        }
        if (x) fact[++fn] = p2(p[i], x);
      }
      if (b > 1) fact[++fn] = p2(b, 1);
      int cnt = solve(1, 1);      
      printf("Case %d: %s\n", ++nc, (cnt & 1) ? "On" : "Off");
    }
  }
} 
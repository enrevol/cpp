#include <algorithm>
#include <bitset>
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
 
const long long thr = 1e10;
 
std::bitset<1500> sv;
int p[500];
int pn;
int cnt[2020202];
long long mod;
 
std::map<int, int> ft;
int vx[33], cx;
int vz[33], cz;
 
inline long long multi(long long x, long long y) {
  long long res = 0;
  while (y) {
    if (y & 1) res = (res + x) % mod;
    x = (x << 1) % mod;
    y >>= 1;
  }
  return res;
}
 
inline int pmod(int x, int y) {
  int res = 1;
  while (y) {
    if (y & 1) res = (1ll * res * x) % mod;
    x = (1ll * x * x) % mod;
    y >>= 1;
  }
  return res;
}
 
inline int nCk(int n, int k) {
  return 1ll * ft[n] * pmod((1ll * ft[k] * ft[n - k]) % mod, mod - 2) % mod;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, m;
  scanf("%d %d %lld", &n, &m, &mod);
  int x = n;
  int y = m - 1;
  int z = m + n - 1;
  if (x > y) std::swap(x, y);
  const int th = 1e6;
  long long ans = -1;
  if (n <= th && m <= th) {
    for (int i = 3; i * i < 1500; i += 2)
      if (!sv[i >> 1])
        for (int j = i * i; j < 1500; j += i << 1)
          sv[j >> 1] = 1;
    p[++pn] = 2;
    for (int i = 3; i < 1500; i += 2)
      if (!sv[i >> 1])
        p[++pn] = i;
    for (int i = y + 1; i <= z; ++i) {
      int t = i;
      for (int j = 1; j <= pn && p[j] * p[j] <= t; ++j)
        while (t % p[j] == 0)
          t /= p[j], ++cnt[p[j]];
      if (t > 1) ++cnt[t];
    }
    for (int i = 2; i <= x; ++i) {
      int t = i;
      for (int j = 1; j <= pn && p[j] * p[j] <= t; ++j)
        while (t % p[j] == 0)
          t /= p[j], --cnt[p[j]];
      if (t > 1) --cnt[t];
    }
    ans = 1;
    for (int i = 2; i < 2000000; ++i)
      while (cnt[i]--)
        if (mod <= thr) ans = (ans * i) % mod;
        else            ans = multi(ans, i);
  } else {    
    while (x) vx[++cx] = x % mod, x /= mod;
    while (z) vz[++cz] = z % mod, z /= mod;
    if (cx > cz) { puts("0"); return 0; }
    int arr[222];
    int sz = 0;
    for (int i = 1; i <= cz; ++i) {
      if (vx[i] > vz[i]) { puts("0"); return 0; }
      arr[++sz] = vz[i];
      arr[++sz] = vx[i];
      arr[++sz] = vz[i] - vx[i];
    }    
    sz = std::unique(arr + 1, arr + sz + 1) - arr - 1;
    std::sort(arr + 1, arr + sz + 1);
    arr[0] = 0;
    ft[0] = 1;
    int val = 1;
    for (int i = 1; i <= sz; ++i) {
      for (int j = arr[i - 1] + 1; j <= arr[i]; ++j)
        val = (1ll * val * j) % mod;
      ft[arr[i]] = val;
    }
    ans = 1;
    for (int i = 1; i <= cz; ++i)
      ans = (ans * nCk(vz[i], vx[i])) % mod;
  }
  assert(ans != -1);
  printf("%lld", ans);
}
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
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

const int N = 100010;

long long tr[N << 2];
int k, a[N], zz[N << 2];

void build(int i, int f, int t) {
  if (f == t) {
    tr[i] = 1ll << a[f];
  } else {
    int m = (f + t) >> 1;
    build(i << 1, f, m);
    build(i << 1 | 1, m + 1, t);
    tr[i] = tr[i << 1] | tr[i << 1 | 1];
  }
}

inline void change(long long& mask, int c) {
  c = ((c % k) + k) % k;
  int v = k - c;
  mask = ((mask & ((1ll << v) - 1)) << c) | (mask >> v);
}

inline void push(int i, int f, int t) {
  if (zz[i]) {
    int m = (f + t) >> 1;
    change(tr[i << 1], zz[i]);
    change(tr[i << 1 | 1], zz[i]);
    if (f < m) zz[i << 1] = (zz[i << 1] + zz[i]) % k;
    if (m + 1 < t) zz[i << 1 | 1] = (zz[i << 1 | 1] + zz[i]) % k;
    zz[i] = 0;
  }
}

void update(int i, int f, int t, int qf, int qt, int c) {
  push(i, f, t);
  if (qf <= f && t <= qt) {
    change(tr[i], c);
    if (f < t) zz[i] = c;
  } else {
    int m = (f + t) >> 1;
    if (qf < m + 1) update(i << 1, f, m, qf, qt, c);
    if (qt > m) update(i << 1 | 1, m + 1, t, qf, qt, c);
    tr[i] = tr[i << 1] | tr[i << 1 | 1];
  }
}

long long query(int i, int f, int t, int qf, int qt) {
  push(i, f, t);
  if (qf <= f && t <= qt) return tr[i];
  int m = (f + t) >> 1;
  if (qt < m + 1) return query(i << 1, f, m, qf, qt);
  if (qf > m) return query(i << 1 | 1, m + 1, t, qf, qt);
  return query(i << 1, f, m, qf, qt) | query(i << 1 | 1, m + 1, t, qf, qt);
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output2.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, q;
  scanf("%d %d %d", &n, &q, &k);
  for (int i = 1; i <= n; ++i)
    scanf("%d", a + i);
  build(1, 1, n);
  while (q--) {
    char s[11];
    scanf("%s", s);
    if (*s == 'A') {
      int f, t, c;
      scanf("%d %d %d", &f, &t, &c);
      update(1, 1, n, f, t, c % k);
    } else if (*s == 'C') {
      int t, m;
      scanf("%d %d", &t, &m);
      long long mask = 0;
      int f = 1;
      for (int v; m--; ) {
        scanf("%d", &v);
        if (v >= k || v < 0) f = 0;
        if (f) mask |= 1ll << v;
      }
      if (f == 0) {
        puts("0");
      } else {
        int ans = 0;
        for (int lo = 1, hi = t; lo <= hi; ) {
          int mi = (lo + hi) >> 1;
          long long val = query(1, 1, n, mi, t);
          //fprintf(stdout, "lo = %d hi = %d mi = %d mask = %lld val = %lld ins = %lld\n", lo, hi, mi, mask, val, val | mask);
          if ((val | mask) == val) {
            ans = mi;
            lo = mi + 1;
          } else {
            hi = mi - 1;
          }
        }
        printf("%d\n", ans);
      }
    } else {
      int f, t;
      scanf("%d %d", &f, &t);
      long long mask = query(1, 1, n, f, t);
      int ans = __builtin_popcountll(mask);
      printf("%d\n", ans);
    }
  }
}

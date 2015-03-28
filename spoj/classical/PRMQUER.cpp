#include <algorithm>
#include <bitset>
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
const int MAX = 10000001;
const int INF = 0x3c3c3c3c;

std::bitset<(MAX >> 1) + 10> sv;
int a[N], tree[N << 2], lazy[N << 2];

inline bool is_prime(int x) {
  return x == 2 || (1 < x && x < MAX && (x & 1) && !sv[x >> 1]);
}

inline void assign(int i, int f, int t, int v) {
  if (f == t) a[f] = v;
  tree[i] = is_prime(v) * (t - f + 1);
  lazy[i] = v;
}

inline void push(int i, int f, int t) {
  if (f < t && lazy[i] > -INF) {
    int m = (f + t) >> 1;
    assign(i << 1, f, m, lazy[i]);
    assign(i << 1 | 1, m + 1, t, lazy[i]);
    lazy[i] = -INF;
  }
}

void add(int i, int f, int t, int p, int v) {
  push(i, f, t);
  if (f == t) {
    a[f] += v;
    tree[i] = is_prime(a[f]);
  } else {
    int m = (f + t) >> 1;
    if (p < m + 1) add(i << 1, f, m, p, v);
    else add(i << 1 | 1, m + 1, t, p, v);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
  }
}

void modify(int i, int f, int t, int qf, int qt, int v) {
  push(i, f, t);
  if (qf <= f && t <= qt) {
    assign(i, f, t, v);
  } else {
    int m = (f + t) >> 1;
    if (qf < m + 1) modify(i << 1, f, m, qf, qt, v);
    if (qt > m) modify(i << 1 | 1, m + 1, t, qf, qt, v);
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
  }
}

int query(int i, int f, int t, int qf, int qt) {
  push(i, f, t);
  if (qf <= f && t <= qt) return tree[i];
  int m = (f + t) >> 1;
  if (qt < m + 1) return query(i << 1, f, m, qf, qt);
  if (qf > m) return query(i << 1 | 1, m + 1, t, qf, qt);
  return query(i << 1, f, m, qf, qt) + query(i << 1 | 1, m + 1, t, qf, qt);
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  for (int i = 3; i * i < MAX; i += 2)
    if (!sv[i >> 1])
      for (int j = i * i; j < MAX; j += i << 1)
        sv[j >> 1] = 1;
  int n, m;
  scanf("%d %d", &n, &m);
  std::fill(lazy + 1, lazy + (N << 2), -INF);
  for (int i = 1; i <= n; ++i) {
    int v;
    scanf("%d", &v);
    add(1, 1, n, i, v);
  }
  while (m--) {
    char s[3];
    scanf("%s", s);
    if (*s == 'A') {
      int p, v;
      scanf("%d %d", &v, &p);
      add(1, 1, n, p, v);
    } else if (*s == 'R') {
      int f, t, v;
      scanf("%d %d %d", &v, &f, &t);
      modify(1, 1, n, f, t, v);
    } else {
      int f, t;
      scanf("%d %d", &f, &t);
      int ans = query(1, 1, n, f, t);
      printf("%d\n", ans);
    }
  }
}
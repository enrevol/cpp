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

const int w = 2e6;

int tr[1 << 22], zz[1 << 22];
int k;

struct ele {
  int g, x, y;
  int f, t;
  void ff() {
    int nx = x - y;
    int ny = x + y;
    x = nx;
    y = ny;
    t = std::min(w, y + k);
    f = y;
  }
  bool operator< (const ele& a) const {
    return x < a.x;
  }
} a[101010];

void push(int i, int f, int t) {  
  if (zz[i]) {
    if (f < t) {
      tr[i << 1] += zz[i];
      tr[i << 1 | 1] += zz[i];
      zz[i << 1] += zz[i];
      zz[i << 1 | 1] += zz[i];
    }
    zz[i] = 0;
  }
}

void modify(int i, int f, int t, int qf, int qt, int v) {
  push(i, f, t);
  if (qf <= f && t <= qt) {
    tr[i] += v;
    zz[i] += v;
  } else {
    int il = i << 1;
    int ir = i << 1 | 1;
    int m = (f + t) >> 1;
    if (qf < m + 1) modify(il, f, m, qf, qt, v);
    if (qt > m) modify(ir, m + 1, t, qf, qt, v);
    tr[i] = std::max(tr[il], tr[ir]);
  }
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  assert(freopen("lazy.in", "r", stdin));
  assert(freopen("lazy.out", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d %d", &n, &k);
  k <<= 1;
  for (int i = 1; i <= n; ++i) {
    scanf("%d %d %d", &a[i].g, &a[i].x, &a[i].y);
    a[i].ff();
  }
  std::sort(a + 1, a + n + 1);
  int ans = 0;
  int j = 1;
  for (int i = 1; i <= n; ++i) {
    while (a[j].x + k < a[i].x) {
      modify(1, 0, w, a[j].f, a[j].t, -a[j].g);
      ++j;
    }
    modify(1, 0, w, a[i].f, a[i].t, a[i].g);
    push(1, 0, w);    
    int val = tr[1];
    if (val > ans) ans = val;
  }
  printf("%d", ans);
}

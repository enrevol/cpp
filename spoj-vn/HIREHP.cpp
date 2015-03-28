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

const int N = 500010;
const long long INF = 0x3c3c3c3c3c3c3c3cLL;

long long zz[N * 4];

void push(int i, int f, int t) {
  if (f < t && zz[i] < INF) {
    int l = i << 1;
    int r = i << 1 | 1;
    if (zz[i] < zz[l]) zz[l] = zz[i];
    if (zz[i] < zz[r]) zz[r] = zz[i];
    zz[i] = INF;
  }
}

void update(int i, int f, int t, int qf, int qt, long long val) {
  push(i, f, t);
  if (qf <= f && t <= qt) {
    if (val < zz[i]) zz[i] = val;
  } else {
    int m = (f + t) >> 1;
    int l = i << 1;
    int r = i << 1 | 1;
    if (qf < m + 1) update(l, f, m, qf, qt, val);
    if (qt > m) update(r, m + 1, t, qf, qt, val);
  }
}

long long query(int i, int f, int t, int p) {
  push(i, f, t);
  if (f == t) return zz[i];
  int m = (f + t) >> 1;
  if (p < m + 1) return query(i << 1, f, m, p);
  return query(i << 1 | 1, m + 1, t, p);
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  memset(zz, 0x3c, sizeof(zz));
  int n;
  scanf("%d", &n);  
  for (int i = 1; i <= n; ++i) {
    long long val = i == 1 ? 0 : query(1, 1, n, i - 1);
    //fprintf(stderr, "val = %lld\n", val);
    int t, p;
    scanf("%d %d", &t, &p);
    update(1, 1, n, i, t, p + val);
  }
  long long ans = query(1, 1, n, n);
  printf("%lld", ans);
}

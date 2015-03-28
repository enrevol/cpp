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

const int N = 610;

int fw[N][N], a[N][N];

inline int query(int x, int y) {
  int r = 0;
  for (int i = x; i; i &= i - 1)
    for (int j = y; j; j &= j - 1)
      r ^= fw[i][j];
  return r;
}

inline int query(int x1, int y1, int x2, int y2) {
  int r = 0;
  r ^= query(x1 - 1, y1 - 1);
  r ^= query(x2, y2);
  r ^= query(x2, y1 - 1);
  r ^= query(x1 - 1, y2);
  return r;
}

void update(int x, int y, int v) {
  for (int i = x; i < N; i += i & -i)
    for (int j = y; j < N; j += j & -j)
      fw[i][j] ^= v;
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      scanf("%d", a[i] + j);
      update(i, j, a[i][j]);
    }
  int q;
  scanf("%d", &q);
  while (q--) {
    int k, x1, y1, x2, y2, v;
    scanf("%d %d %d", &k, &x1, &y1);
    ++x1, ++y1;
    if (k == 0) {
      scanf("%d %d", &x2, &y2);
      ++x2, ++y2;
      printf("%d\n", query(x1, y1, x2, y2));
    } else {
      scanf("%d", &v);
      update(x1, y1, a[x1][y1]);
      a[x1][y1] = v;
      update(x1, y1, a[x1][y1]);
    }
  }
}
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
 
const int w = 5e4;
 
int tx[w * 2 + 5]; // max
int ty[w * 2 + 5]; // min
 
inline void updatex(int i, int v) {
  for (i += w; i; i >>= 1)
    tx[i] = std::max(tx[i], v);
}
 
inline void updatey(int i, int v) {
  for (i += w; i; i >>= 1)
    ty[i] = std::min(ty[i], v);
}
 
inline int queryx(int f, int t) {
  int res = 0;
  for (f += w, t += w + 1; f < t; f >>= 1, t >>= 1) {
    if (f & 1) res = std::max(res, tx[f++]);
    if (t & 1) res = std::max(res, tx[--t]);
  }
  return res;
}
 
inline int queryy(int f, int t) {
  int res = 0x3c3c3c3c;
  for (f += w, t += w + 1; f < t; f >>= 1, t >>= 1) {
    if (f & 1) res = std::min(res, ty[f++]);
    if (t & 1) res = std::min(res, ty[--t]);
  }
  return res;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  memset(ty, 0x3c, sizeof(ty));
  int n, q;
  scanf("%d %d", &n, &q);
  for (int i = 1, v; i <= n; ++i) {
    scanf("%d", &v);
    updatex(i, v);
    updatey(i, v);
  }
  while (q--) {
    int f, t;
    scanf("%d %d", &f, &t);
    printf("%d\n", queryx(f, t) - queryy(f, t));
  }
}
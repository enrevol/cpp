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
 
int fw[1025][1025];
 
inline int query(int x, int y) {
  int res = 0;
  for (int i = x; i; i -= i & -i)
    for (int j = y ; j; j -= j & -j)
      res += fw[i][j];
  return res;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%*d %d", &n);
  int k;
  while (scanf("%d", &k)) {
    if (k == 3) break;
    if (k == 1) {
      int x, y, v;
      scanf("%d %d %d", &x, &y, &v);
      ++x, ++y;
      for (int i = x; i <= n; i += i & -i)
        for (int j = y; j <= n; j += j & -j)
          fw[i][j] += v;
    } else {
      int fx, fy, tx, ty;      
      scanf("%d %d %d %d", &fx, &fy, &tx, &ty);
      ++fx, ++fy, ++tx, ++ty;
      printf("%d\n", query(tx, ty) - query(fx - 1, ty) - query(tx, fy - 1) + query(fx - 1, fy - 1));
    }
  }
}
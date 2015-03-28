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
 
// 0 = I
// 1 = D
// 2 = K
// 3 = C
int t[202020];
int a[202020];
 
int vn;
int v[202020];
int fw[202020];
 
bool b[202020];
 
void update(int i, int v) {
  for ( ; i <= vn; i += i & -i)
    fw[i] += v;    
}
 
int query(int i) {
  int res = 0;
  for ( ; i >= 1; i -= i & -i)
    res += fw[i];
  return res;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int q;
  scanf("%d", &q);  
  for (int i = 1; i <= q; ++i) {
    char s[3];
    scanf("%s %d", s, a + i);
    switch (*s) {
      case 'I': t[i] = 0; v[++vn] = a[i]; break;
      case 'D': t[i] = 1; v[++vn] = a[i]; break;
      case 'K': t[i] = 2; break;
      case 'C': t[i] = 3; break;
    }
  }
  std::sort(v + 1, v + vn + 1);
  vn = std::unique(v + 1, v + vn + 1) - v - 1;
  int tot = 0;
  for (int i = 1; i <= q; ++i) {
    if (t[i] == 0) {
      int p = std::lower_bound(v + 1, v + vn + 1, a[i]) - v;
      if (!b[p]) {
        ++tot;
        update(p, 1);
        b[p] = 1;
      }
    } else if (t[i] == 1) {
      int p = std::lower_bound(v + 1, v + vn + 1, a[i]) - v;
      if (b[p]) {
        --tot;
        update(p, -1);
        b[p] = 0;
      }
    } else if (t[i] == 2) {
      if (a[i] > tot) {
        puts("invalid");
      } else {
        int res = -1;
        for (int lo = 1, hi = vn; lo <= hi; ) {
          int mi = (lo + hi) >> 1;
          int cnt = query(mi);
          if (cnt >= a[i]) {
            res = mi;
            hi = mi - 1;
          } else {
            lo = mi + 1;
          }
        }
        printf("%d\n", v[res]);
      }
    } else {
      int p = std::lower_bound(v + 1, v + vn + 1, a[i]) - v - 1;
      printf("%d\n", query(p));
    }
  }
}
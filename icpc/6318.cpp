#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
int a[111][111], d[111], e[111];
 
bool ff(int a, int b) {
  return d[a] > d[b];
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int c, v;
    scanf("%d %d", &c, &v);
    memset(d, 0, sizeof(d));
    for (int i = 1; i <= v; ++i) {
      for (int j = 1; j <= c; ++j)
        scanf("%d", a[i] + j);
      ++d[a[i][1]];      
    }
    for (int i = 1; i <= c; ++i)
      e[i] = i;
    std::sort(e + 1, e + c + 1, ff);
    int p = e[1];
    if ((d[p] << 1) > v) {
      printf("%d 1\n", p);
    } else {
      int q = e[2];
      d[p] = d[q] = 0;
      for (int i = 1; i <= v; ++i)
        for (int j = 1; j <= c; ++j)
          if (a[i][j] == p || a[i][j] == q) {
            ++d[a[i][j]];
            break;
          }
      printf("%d 2\n", d[p] > d[q] ? p : q);      
    }
  }
}
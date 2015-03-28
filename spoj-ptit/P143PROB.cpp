#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
struct ss {
  int u, v;
  double p;
} e[10101];
 
double a[111], b[111];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n, m, t;
    scanf("%d %d %d", &n, &m, &t);
    for (int i = 1; i <= n; ++i)
      scanf("%lf", a + i);
    for (int i = 1; i <= m; ++i) {
      scanf("%d %d %lf", &e[i].u, &e[i].v, &e[i].p);
      ++e[i].u;
      ++e[i].v;
    }
    while (t--) {
      memset(b, 0, sizeof(b));      
      for (int i = 1; i <= m; ++i) {
        b[e[i].u] -= a[e[i].u] * e[i].p;
        b[e[i].v] += a[e[i].u] * e[i].p;
      }
      for (int i = 1; i <= n; ++i)
        a[i] += b[i];
    }
    memset(b, 0, sizeof(b));
    for (int i = 1; i <= m; ++i) {
      b[e[i].u] += a[e[i].v];
      b[e[i].v] += a[e[i].u];
    }
    for (int i = 1; i <= n; ++i)
      a[i] += b[i];
    double ans = a[1];
    for (int i = 2; i <= n; ++i)
      if (ans > a[i]) ans = a[i];
    printf("%.15lf\n", ans);
  }
}
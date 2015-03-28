#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
int a[101], b[101];
int c[101], d[101];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  int x, y;
  for (int i = 1; i <= n; ++i) {
    scanf("%d %d", &x, &y);
    ++a[x];
    ++b[y];
    std::copy(a + 1, a + 101, c + 1);
    std::copy(b + 1, b + 101, d + 1);
    int f = 1;
    int t = 100;
    int ans = 0;
    while (f <= 100 && t >= 1) {
      if (!c[f]) {
        ++f;
      } else if (!d[t]) {
        --t;
      } else {
        int p = c[f] > d[t] ? d[t] : c[f];
        int val = f + t;
        if (val > ans) ans = val;
        c[f] -= p;
        d[t] -= p;
      }
    }
    printf("%d\n", ans);
  }
} 
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
 
char s[222];
int x[22], y[22];
double dp[1 << 16];
 
double dist(const int& x_1, const int& y_1, const int& x_2, const int& y_2) {
  return sqrt((x_1 - x_2) * (x_1 - x_2) + (y_1 - y_2) * (y_1 - y_2));
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n, n_case = 0;
  while (1) {
    scanf("%d", &n);
    if (n == 0) break;
    n <<= 1;
    for (int i = 0; i < n; ++i)
      scanf("%s %d %d", s + 1, x + i, y + i);
    for (int mask = 1; mask < (1 << n); ++mask) {
      int cnt = 0;
      int t = mask;
      while (t) {
        cnt += t & 1;
        t >>= 1;
      }
      if (!(cnt & 1)) {
        dp[mask] = 1e9;
        for (int i = 0; i < n; ++i)
          if (mask & (1 << i))
            for (int j = i + 1; j < n; ++j)
              if (mask & (1 << j)) {
                double val = dp[(mask ^ (1 << i)) ^ (1 << j)] + dist(x[i], y[i], x[j], y[j]);
                if (val < dp[mask]) dp[mask] = val;
              }
      }
    }
    printf("Case %d: %.2lf\n", ++n_case, dp[(1 << n) - 1]);
  }
}
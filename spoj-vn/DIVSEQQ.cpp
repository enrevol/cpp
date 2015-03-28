#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
int a[101010];
int dp[101010][18];
long long ps[101010];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, q, m;
  scanf("%d %d %d", &n, &q, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a + i);
    ps[i] = ps[i - 1] + a[i];
  }
  int k = n;
  for (int i = n; i >= 1; --i) {
    while (k - 1 >= 1 && ps[i] - ps[k - 2] <= m)
      --k;
    dp[i][0] = k;
  }
  for (int j = 1; j < 18; ++j)
    for (int i = n; i >= 1; --i)
      dp[i][j] = std::max(dp[dp[i][j - 1] - 1][j - 1], 1);
  while (q--) {
    int u, v;
    scanf("%d %d", &u, &v);
    if (v > n) v = n;
    for (int i = 17; i >= 0; --i)
      if (v >= 1 << i) {
        v -= 1 << i;
        u = dp[u][i];
        if (v == 0 || u == 1) break;
        --u;
      }    
    printf("%d\n", u);
  }
} 
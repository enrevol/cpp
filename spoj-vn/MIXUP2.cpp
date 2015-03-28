#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
int a[16];
long long dp[1 << 16][16];
 
int abs(int a) {
  return a >= 0 ? a : -a;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, k;
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; ++i)
    scanf("%d", a + i);
  for (int i = 0; i < n; ++i)
    dp[0][i] = 1;
  for (int mask = 0; mask < 1 << n; ++mask)
    for (int i = 0; i < n; ++i)
      if (mask & (1 << i)) {
        int nmask = mask ^ (1 << i);
        if (nmask) {
          for (int j = 0; j < n; ++j)
            if (nmask & (1 << j))
              if (abs(a[i] - a[j]) > k)
                dp[mask][i] += dp[nmask][j];
        } else {
          ++dp[mask][i];
        }
      }
  long long ans = 0;
  for (int i = 0; i < n; ++i)
    ans += dp[(1 << n) - 1][i];
  printf("%lld", ans);
} 
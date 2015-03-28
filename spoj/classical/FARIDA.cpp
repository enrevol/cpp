#include <algorithm>
#include <cstdio>
#include <cstring>
 
long long dp[10101];
int a[10101];
 
int main() {
  int tt, n_case = 0;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d", a + i);
    memset(dp, 0, sizeof(dp));
    dp[1] = a[1];
    dp[2] = std::max(a[1], a[2]);
    for (int i = 3; i <= n; ++i)
      dp[i] = std::max(dp[i - 1], dp[i - 2] + a[i]);
    printf("Case %d: %lld\n", ++n_case, dp[n]);
  }
} 
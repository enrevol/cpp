#include <cstdio>
#include <cstring>
 
char s[5050];
unsigned long long dp[5050];
 
int main() {
  while (scanf("%s", s + 1)) {
    int sz = strlen(s + 1);
    if (s[1] == '0' && sz == 1) break;
    memset(dp, 0, sizeof(dp));
    dp[0] = dp[1] = 1;
    for (int i = 2; i <= sz; ++i) {
      if (s[i] != '0')
        dp[i] += dp[i - 1];
      if (s[i - 1] == '1' || (s[i - 1] == '2' && s[i] <= '6'))
        dp[i] += dp[i - 2];
    }
    printf("%llu\n", dp[sz]);
  }
}
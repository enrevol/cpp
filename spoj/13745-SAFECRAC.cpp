#include <algorithm>
#include <cstdio>
 
const long long mod = 1000000007;
 
long long a[101010][11];
 
int main() {
  for (int i = 0; i < 10; ++i)
    a[1][i] = 1;
  for (int i = 2; i <= 100000; ++i) {
    a[i][0] = a[i - 1][7];
    a[i][1] = (a[i - 1][2] + a[i - 1][4]) % mod;
    a[i][2] = (a[i - 1][1] + a[i - 1][3] + a[i - 1][5]) % mod;
    a[i][3] = (a[i - 1][2] + a[i - 1][6]) % mod;
    a[i][4] = (a[i - 1][1] + a[i - 1][5] + a[i - 1][7]) % mod;
    a[i][5] = (a[i - 1][2] + a[i - 1][4] + a[i - 1][6] + a[i - 1][8]) % mod;
    a[i][6] = (a[i - 1][3] + a[i - 1][5] + a[i - 1][9]) % mod;
    a[i][7] = (a[i - 1][4] + a[i - 1][8] + a[i - 1][0]) % mod;
    a[i][8] = (a[i - 1][5] + a[i - 1][7] + a[i - 1][9]) % mod;
    a[i][9] = (a[i - 1][6] + a[i - 1][8]) % mod;
  }
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);
    long long ans = 0;
    for (int i = 0; i < 10; ++i)
      ans += a[n][i];
    printf("%lld\n", (ans % mod));
  }
} 
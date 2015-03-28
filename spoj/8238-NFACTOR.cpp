#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <vector>
 
std::bitset<2020> is_prime;
std::vector<int> primes;
int ans[11][1010101];
 
int main() {
  //freopen("input.txt", "r", stdin);
  for (int i = 2; i <= 1000; ++i)
    is_prime[i] = 1;
  for (int i = 2; i <= 35; ++i)
    if (is_prime[i])
      for (int j = i * i; j <= 1000; j += i)
        is_prime[j] = 0;
  for (int i = 2; i <= 1000; ++i)
    if (is_prime[i]) primes.push_back(i);
  for (int i = 1; i <= 1000000; ++i)
    ans[0][i] = 1;
  for (int i = 1; i <= 1000000; ++i) {
    int num = 0;
    int t = i;
    int idx = 0;
    while (idx < primes.size() && primes[idx] * primes[idx] <= t) {
      int k = 0;
      while (t % primes[idx] == 0) {
        t /= primes[idx];
        k = 1;
      }
      num += k;
      ++idx;
    }
    if (t > 1) ++num;
    ++ans[num][i];
  }
  for (int i = 1; i <= 7; ++i)
    for (int j = 1; j <= 1000000; ++j)
      ans[i][j] += ans[i][j - 1];
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int a, b, n;
    scanf("%d %d %d", &a, &b, &n);
    printf("%d\n", ans[n][b] - ans[n][a - 1]);
  }
} 
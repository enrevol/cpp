#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <vector>
 
std::bitset<40404> is_prime;
std::vector<int> primes;
 
int main() {
  //freopen("input.txt", "r", stdin);
  for (int i = 2; i <= 40000; ++i)
    is_prime[i] = 1;
  for (int i = 2; i <= 200; ++i)
    if (is_prime[i])
      for (int j = i * i; j <= 40000; j += i)
        is_prime[j] = 0;
  for (int i = 2; i <= 40000; ++i)
    if (is_prime[i]) primes.push_back(i);
  int a, b, n;
  scanf("%d %d %d", &a, &b, &n);
  int ans = 0;  
  for (int i = a; i <= b; ++i) {
    int num = 1;
    int t = i;
    int idx = 0;
    while (idx < primes.size() && primes[idx] * primes[idx] <= t) {
      int k = 0;
      while (t % primes[idx] == 0) {
        t /= primes[idx];
        ++k;
      }
      num *= (k + 1);
      ++idx;
    }
    if (t > 1) num <<= 1;
    if (num == n) ++ans;
  }
  printf("%d", ans);
} 
#include <bitset>
#include <cstdio>
#include <cstring>
#include <vector>
 
std::bitset<3333> sieve;
std::vector<int> prime;
 
int main() {
  for (int i = 2; i <= 3222; ++i)
    sieve[i] = 1;
  for (int i = 2; i * i <= 3222; ++i)
    if (sieve[i])
      for (int j = i * i; j <= 3222; j += i)
        sieve[j] = 0;
  for (int i = 2; i <= 3222; ++i)
    if (sieve[i])
      prime.push_back(i);
  int tt;
  scanf("%d", &tt);  
  while (tt--) {
    int n;
    scanf("%d", &n);
    int idx = 0, even = 0, odd = 0;    
    while (idx < prime.size() && prime[idx] * prime[idx] <= n ) {
      int t = 0;
      while (n % prime[idx] == 0) {
        n /= prime[idx];
        ++t;
      }
      if (t) {
        if (t & 1) ++odd;
        else ++even;
      }
      ++idx;
    }
    if (n > 1) ++odd;
    if (even > odd) puts("Psycho Number");
    else puts("Ordinary Number");
  }        
} 
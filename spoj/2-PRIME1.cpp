#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <vector>
 
std::bitset<101010> sieve;
int a[101010];
 
int main() {
  sieve[1] = 1;
  for (int i = 2; i <= 316; ++i)
    if (!sieve[i])
      for (int j = i * i; j <= 100000; j += i)
        sieve[j] = 1;
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    memset(a, 0, sizeof(a));
    int m, n;
    scanf("%d %d", &m, &n);
    for (int i = 2; i <= 100000; ++i)
      if (!sieve[i])
        for (int j = ((m - 1) / i + 1) * i; j <= n; j += i)   
          a[j - m] = 1;
    for (int i = 0; i <= n - m; ++i)
      if ((!a[i] && i + m > 100000) || (i + m <= 100000 && !sieve[i + m]))
        printf("%d\n", i + m);
    putchar('\n');    
  }
} 
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
 
int main() {
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    long long n;
    scanf("%lld", &n);
    long long a = n >> 1;
    while (std::__gcd(a, n) > 1) --a;
    printf("%lld\n", a);
  }
} 
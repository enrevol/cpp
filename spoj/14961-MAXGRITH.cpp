#include <algorithm>
#include <cstdio>
#include <cstring>
 
int main() {
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    long long n;
    scanf("%lld", &n);
    printf("%lld\n", (n * 2 / 3 + (n % 3 > 0)) % 1000000007);
  }  
} 
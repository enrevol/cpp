#include <algorithm>
#include <cstdio>
#include <map>
 
const long long mod = 1000000003;
 
long long a[1010101], b[1010101];
 
int main() {  
  for (int i = 1; i <= 1000000; ++i) {
    a[i] = (a[i - 1] + 1ll * i * i * i) % mod;
    b[i] = (b[i - 1] + a[i]) % mod;
  }
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);
    printf("%lld\n", b[n]);
  }
} 
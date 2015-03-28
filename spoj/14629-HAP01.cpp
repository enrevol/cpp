#include <algorithm>
#include <cstdio>
 
int main() {
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    long long m, n;
    int k;
    scanf("%lld %lld %d", &m, &n, &k);
    int a, b, f;
    long long t;
    int ans = 0;
    for (long long i = m; i <= n; ++i) {
      a = b = f = 0;
      t = i;
      while (t) {
        if (f) a += t & 1;
        else b += t & 1;
        t >>= 1;
        f ^= 1;
      }
      if (std::abs(a - b) == k) ++ans;
    }
    printf("%d\n", ans);
  }
} 
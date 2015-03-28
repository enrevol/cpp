#include <algorithm>
#include <cstdio>
 
int a[101010];
long long sum[303030];
 
int main() {
  int n;
  scanf("%d", &n);
  for (int i = n; i >= 1; --i)
    scanf("%d", a + i);
  for (int i = 1; i <= n; ++i)
    sum[i] = sum[i - 1] + a[i];
  int q;
  scanf("%d", &q);
  int x, y, z;  
  while (q--) {
    scanf("%d %d", &x, &y);
    if (x == 1) {
      scanf("%d", &z);
      printf("%lld\n", sum[n - y + 1] - sum[n - z]);
    } else {
      ++n;
      sum[n] = sum[n - 1] + y;
    }
  }
} 
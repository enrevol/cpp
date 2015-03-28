#include <algorithm>
#include <cstdio>
 
int a[101010];
 
int main() {
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i)
      scanf("%d", a + i);
    std::sort(a + 1, a + n + 1);
    int ans = 0;
    int l = 1, r = n;
    while (l < r) {
      if (a[l] + a[r] == m) {
        ++l;
        --r;
        ++ans;
      } else if (a[l] + a[r] < m) {
        ++l;
      } else {
        --r;
      }
    }
    printf("%d\n", ans);
  }
} 
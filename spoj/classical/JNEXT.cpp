#include <algorithm>
#include <cstdio>
 
int a[1010101];
 
int main() {
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d", a + i);
    int f = 0;
    for (int i = n - 1; i >= 1 && !f; --i)
      if (a[i] < a[i + 1]) f = i;
    if (f) {
      int idx = f + 1;
      while (idx + 1 <= n && a[idx + 1] > a[f]) ++idx;
      std::next_permutation(a + f, a + n + 1);
      for (int i = 1; i <= n; ++i)
        printf("%d", a[i]);
      putchar('\n');
    } else {
      puts("-1");
    }
  }
} 
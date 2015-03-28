#include <cstdio>
 
int a[1010], b[1010];
 
int main() {
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);
    int best = 1;
    for (int i = 1; i <= n; ++i) {
      scanf("%d %d", a + i, b + i);
      if (a[best] < a[i]) best = i;
    }
    int f = 1;
    for (int i = 1; i <= n && f; ++i)
      if (a[best] < b[i] && i != best) f = 0;
    if (f) {
      printf("%d\n", best);
    } else {
      puts("-1");
    }
  }
} 
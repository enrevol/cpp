#include <cstdio>
 
int main() {
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n, a;
    scanf("%d", &n);
    long long s = 0;
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &a);
      s += a;
    }
    if (s % n == 0) {
      printf("%d\n", n);
    } else {
      printf("%d\n", n - 1);
    }
  }
} 
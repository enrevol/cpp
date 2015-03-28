#include <cstdio>
 
int ans[101];
 
int main() {
  ans[1] = 1;
  for (int i = 2; i <= 100; ++i) {
    ans[i] = ans[i - 1];
    for (int j = 1; j <= i; ++j)
      ans[i] += (i - j) * 2 + 1;
  }
  int n;
  while (scanf("%d", &n)) {
    if (n == 0) break;
    printf("%d\n", ans[n]);
  }
} 
#include <cstdio>
#include <cstring>
 
int ans[1010];
 
int main() {
  memset(ans, 1, sizeof(ans));
  ans[0] = 0;
  for (int i = 1; i <= 1000; ++i)
    for (int j = 1; j * j <= i; ++j)
      if (ans[i - j * j] + 1 < ans[i])
        ans[i] = ans[i - j * j] + 1;
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);
    printf("%d\n", ans[n]);
  }
} 
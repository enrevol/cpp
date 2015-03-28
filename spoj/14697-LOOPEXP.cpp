#include <algorithm>
#include <cstdio>
 
double ans[101010];
 
int main() {
  ans[1] = 1;
  for (int i = 2; i <= 100000; ++i)
    ans[i] = ans[i - 1] + double(1) / i;
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);
    printf("%.17lf\n", ans[n]);
  }
} 
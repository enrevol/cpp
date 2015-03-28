#include <cstdio>

int g[1010][1010];
int a[1010];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      scanf("%d", &g[i][j]);
  a[1] = a[n] = 1;
  for (int i = 2; i < n; ++i)
    a[i] = (g[i - 1][i] + g[i][i + 1] - g[i - 1][i + 1]) / 2;
  a[1] = g[1][2] - a[2];
  a[n] = g[n - 1][n] - a[n - 1];
  for (int i = 1; i <= n; ++i)
    printf("%d ", a[i]);
}
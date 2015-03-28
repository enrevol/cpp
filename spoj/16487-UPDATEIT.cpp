#include <cstdio>
#include <cstring>
 
int a[10101];
 
int main() {
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    memset(a, 0, sizeof(a));
    int n, u;
    scanf("%d %d", &n, &u);
    int l, r, val;
    while (u--) {
      scanf("%d %d %d", &l, &r, &val);
      a[l + 1] += val;
      a[r + 2] -= val;
    }
    for (int i = 1; i <= n; ++i)
      a[i] += a[i - 1];
    int q;
    scanf("%d", &q);
    int idx;
    while (q--) {
      scanf("%d", &idx);
      printf("%d\n", a[idx + 1]);
    }
  }
} 
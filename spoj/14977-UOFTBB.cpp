#include <algorithm>
#include <cstdio>
#include <cstring>
 
long long d_tot[1010];
 
int main() {
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int l, n, c, r, d, h;
    scanf("%d %d", &l, &n);
    memset(d_tot, 0, sizeof(d_tot));
    for (int i = 1; i <= n; ++i) {
      scanf("%d %d %d", &c, &r, &d);
      d_tot[std::max(1, c - r)] += d;
      d_tot[std::min(l, c + r) + 1] -= d;
    }    
    for (int i = 1; i <= l; ++i)
      d_tot[i] += d_tot[i - 1];
    int m;
    scanf("%d", &m);
    while (m--) {
      scanf("%d", &h);
      int f = 0;
      for (int i = 1; i <= l && !f; ++i) {
        if (h > d_tot[i]) h -= d_tot[i];
        else f = i;
      }
      if (f) printf("%d\n", f);
      else puts("Bloon leakage");
    }
  }
} 
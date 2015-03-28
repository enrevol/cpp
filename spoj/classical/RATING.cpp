#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
struct ss {
  int a, h, i;
} a[303030];
 
int tr[20][303030], ans[303030];
 
void build(int d, int f, int t) {
  if (f == t) {
    tr[d][f] = a[f].h;
  } else {
    int m = (f + t) >> 1;
    build(d + 1, f, m);
    build(d + 1, m + 1, t);
    int i = f, l = f, r = m + 1;
    while (l <= m && r <= t) {
      if (tr[d + 1][l] < tr[d + 1][r]) tr[d][i++] = tr[d + 1][l++];
      else                             tr[d][i++] = tr[d + 1][r++];
    }
    while (l <= m) tr[d][i++] = tr[d + 1][l++];
    while (r <= t) tr[d][i++] = tr[d + 1][r++];
  }
}
 
int query(int d, int f, int t, int qf, int qt, int sf, int st) {
  if (qf > qt) return 0;
  if (qf <= f && t <= qt) {
    return std::upper_bound(tr[d] + f, tr[d] + t + 1, st) - std::lower_bound(tr[d] + f, tr[d] + t + 1, sf);
  } else {
    int m = (f + t) >> 1;
    if (qt < m + 1) return query(d + 1, f, m, qf, qt, sf, st);
    if (qf > m) return query(d + 1, m + 1, t, qf, qt, sf, st);
    return query(d + 1, f, m, qf, qt, sf, st) + query(d + 1, m + 1, t, qf, qt, sf, st);
  }
}
 
bool ff(const ss& lhs, const ss& rhs) {
  if (lhs.a == rhs.a) return lhs.h < rhs.h;
  return lhs.a < rhs.a;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d %d", &a[i].a, &a[i].h);
    a[i].i = i;
  }
  std::sort(a + 1, a + n + 1, ff);
  build(0, 1, n);
  for (int i = 1; i <= n; ++i) {
    int lb = std::lower_bound(a + 1, a + n + 1, a[i], ff) - a;
    int ub = std::upper_bound(a + 1, a + n + 1, a[i], ff) - a;
    int v = query(0, 1, n, 1, ub - 1, 1, a[i].h) - (ub - lb);    
    ans[a[i].i] = v;
  }
  for (int i = 1; i <= n; ++i)
    printf("%d\n", ans[i]);
}
 
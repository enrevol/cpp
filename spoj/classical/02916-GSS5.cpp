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
 
int a[1 << 15];
 
struct ss {
  long long l, r, s, b;
} tr[1 << 18];
 
 ss merge(const ss& lhs, const ss& rhs) {
   ss res;
   res.s = lhs.s + rhs.s;
   res.l = std::max(lhs.l, lhs.s + rhs.l);
   res.r = std::max(rhs.r, rhs.s + lhs.r);
   res.b = std::max(lhs.b, rhs.b);
   res.b = std::max(res.b, lhs.r + rhs.l);
   if (res.l > res.b) res.b = res.l;
   if (res.r > res.b) res.b = res.r;
   if (res.s > res.b) res.b = res.s;
   return res;
 }
 
void build(int i, int l, int r) {
  if (l == r) {
    tr[i].l = tr[i].r = tr[i].s = tr[i].b = a[l];
  } else {
    int m = (l + r) >> 1;
    build(i << 1, l, m);
    build(i << 1 | 1, m + 1, r);
    tr[i] = merge(tr[i << 1], tr[i << 1 | 1]);
  }
}
 
ss query(int i, int l, int r, int f, int t) {
  if (f > t) return tr[0];
  if (f <= l && r <= t) {
    return tr[i];
  } else {
    int m = (l + r) >> 1;
    if (t <= m) return query(i << 1, l, m, f, t);
    if (f >= m + 1) return query(i << 1 | 1, m + 1, r, f, t);
    return merge(query(i << 1, l, m, f, t), query(i << 1 | 1, m + 1, r, f, t));
  }
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d", a + i);
    build(1, 1, n);
    int m;
    scanf("%d", &m);
    int lf, lt, rf, rt;
    while (m--) {
      scanf("%d %d %d %d", &lf, &lt, &rf, &rt);
      long long ans = 0;
      ss l = query(1, 1, n, lf, lt);
      ss r = query(1, 1, n, rf, rt);
      if (lt < rf) {
        ss m = query(1, 1, n, lt + 1, rf - 1);
        ans = l.r + m.s + r.l;
      } else {
        ss ml = query(1, 1, n, lf, rf - 1);
        ss m = query(1, 1, n, rf, lt);
        ss mr = query(1, 1, n, lt + 1, rt);
        ans = std::max(ml.r + r.l, l.r + mr.l);
        ans = std::max(ans, ml.r + m.s + mr.l);
        ans = std::max(ans, m.b);
      }
      printf("%lld\n", ans);
    }
  }
}
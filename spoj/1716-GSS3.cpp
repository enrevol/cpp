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
  long long b, l, r, s;
} tr[202020];
 
int a[50505];
 
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
    tr[i].b = tr[i].s = tr[i].l = tr[i].r = a[l];
  } else {
    int il = i << 1;
    int ir = i << 1 | 1;
    int m = (l + r) >> 1;
    build(il, l, m);
    build(ir, m + 1, r);
    tr[i] = merge(tr[il], tr[ir]);
  }
}
 
void modify(int i, int l, int r, int p, int v) {
  if (l == r) {
    tr[i].b = tr[i].s = tr[i].l = tr[i].r = v;
  } else {
    int il = i << 1;
    int ir = i << 1 | 1;
    int m = (l + r) >> 1;
    if (p <= m) modify(il, l, m, p, v);
    else modify(ir, m + 1, r, p, v);
    tr[i] = merge(tr[il], tr[ir]);
  }
}
 
ss query(int i, int l, int r, int f, int t) {
  assert(!(t < l && r < f));
  if (f <= l && r <= t) return tr[i];
  int il = i << 1;
  int ir = i << 1 | 1;
  int m = (l + r) >> 1;
  if (f <= m && m + 1 <= t) return merge(query(il, l, m, f, t), query(ir, m + 1, r, f, t));
  if (f <= m) return query(il, l, m, f, t);
  return query(ir, m + 1, r, f, t);
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", a + i);
  build(1, 1, n);
  int m;
  scanf("%d", &m);
  int t, x, y;
  while (m--) {
    scanf("%d %d %d", &t, &x, &y);
    if (t) printf("%lld\n", query(1, 1, n, x, y).b);
    else modify(1, 1, n, x, y);
  }
} 
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
 
struct node {
  int lc, lv;
  int rc, rv;
  int b;
} tr[1 << 20];
 
int a[100100];
 
node merge(const node& lhs, const node& rhs) {
  node res;
  res.lv = lhs.lv;
  res.lc = lhs.lc;
  res.rv = rhs.rv;
  res.rc = rhs.rc;
  res.b = std::max(lhs.b, rhs.b);
  if (lhs.lv == rhs.lv) res.lc += rhs.lc;
  if (rhs.rv == lhs.rv) res.rc += lhs.rc;
  if (lhs.rv == rhs.lv) res.b = std::max(res.b, lhs.rc + rhs.lc);
  if (res.lc > res.b) res.b = res.lc;
  if (res.rc > res.b) res.b = res.rc;
  return res;
}
 
void build(int i, int l, int r) {
  if (l == r) {
    tr[i].lc = tr[i].rc = tr[i].b = 1;
    tr[i].lv = tr[i].rv = a[l];
  } else {
    int il = i << 1;
    int ir = i << 1 | 1;
    int m = (l + r) >> 1;
    build(il, l, m);
    build(ir, m + 1, r);
    tr[i] = merge(tr[il], tr[ir]);
  }
}
 
node query(int i, int l, int r, int f, int t) {
  if (f <= l && r <= t) {
    return tr[i];
  } else {
    int il = i << 1;
    int ir = i << 1 | 1;
    int m = (l + r) >> 1;
    if (t < m + 1) return query(il, l, m, f, t);
    if (f > m) return query(ir, m + 1, r, f, t);
    return merge(query(il, l, m, f, t), query(ir, m + 1, r, f, t));
  }
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  while (1) {
    int n;
    scanf("%d", &n);
    if (n == 0) break;
    int q;
    scanf("%d", &q);
    for (int i = 1; i <= n; ++i)
      scanf("%d", a + i);
    build(1, 1, n);
    int f, t;
    while (q--) {
      scanf("%d %d", &f, &t);
      printf("%d\n", query(1, 1, n, f, t).b);
    }
  }
} 